/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2014 Stanford University and the Authors.           *
 * Authors: Reginald Francois                                                    *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */
#include "OpenMM.h"
#include "Sqlitefile.h"
#include "openmm/OpenMMException.h"
#include "openmm/internal/AssertionUtilities.h"
#include <fstream>
#include "sqlite3.h"
#include <cstring>

using namespace SqlitefilePlugin;
using namespace OpenMM;
using namespace std;

Sqlitefile::Sqlitefile() {

    // Create a system with bonded forces.
    // Create a system with nonbonded forces.
    system = new OpenMM::System;
    bonds = new OpenMM::HarmonicBondForce();
    nonbond = new OpenMM::NonbondedForce();
    system->addForce(nonbond);
    system->addForce(bonds);


}

int Sqlitefile::Open(string filename) const {
        sqlite3 *db;
        cout<<"From Database:"<<filename<<endl;
        cout<<"The results are: "<<endl;
        double particle;
        int count=0;
        int rc = sqlite3_open(filename.c_str(), &db);



        std::vector<OpenMM::Vec3> initPosIn;

        if (rc != SQLITE_OK) {

           cout<<"Cannot open database: " << sqlite3_errmsg(db)<<endl;
           sqlite3_close(db);


        }


        //sql loop over 'particle' table
        char *sql = "SELECT mass,x,y,z,charge FROM particle";

        sqlite3_stmt *stmt = NULL;
        rc =sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
        while(sqlite3_step(stmt) == SQLITE_ROW){
            double mass = sqlite3_column_double(stmt,   0);
            double x = sqlite3_column_double(stmt,    1);
            double y = sqlite3_column_double(stmt,    2);
            double z = sqlite3_column_double(stmt,    3);
            double charge = sqlite3_column_double(stmt,    4);


            cout<<"Particle number "<<count<<"'s"<<" "<<"X coordinates are "<<x<<" "<<endl;//prints the x coordinate of the particle
            cout<<"Particle number "<<count<<"'s"<<" "<<"Y coordinates are "<<y<<" "<<endl;//prints the y coordinate of the particle
            cout<<"Particle number "<<count<<"'s"<<" "<<"Z coordinates are "<<z<<" "<<endl;//prints the z coordinate of the particle
            cout<<"Particle number "<<count<<"'s"<<" "<<"Charge is "<<charge<<endl; //prints the charge of the particle


            cout<<"Particle number "<<count<<"'s"<<" "<<"mass is"<<" ";
            system->addParticle(mass); // mass of Ar, grams per mole
            nonbond->addParticle(charge, 0, 0);
            cout<<mass<<endl;


          initPosIn.push_back(OpenMM::Vec3(x + 0.001,y,z)); // location, nm


          count++;

        }

            OpenMM::VerletIntegrator integrator(0.00004); // step size in ps
            OpenMM::Context context(*system, integrator);

            context.setPositions(initPosIn);

        //sql loop over stretch_harm_term and stretch_harm_param tables
        char *Sql2 = "Select p0, p1, r0, fc FROM stretch_harm_term INNER JOIN stretch_harm_param ON stretch_harm_term.param=stretch_harm_param.id";
        stmt = NULL;
        rc =sqlite3_prepare_v2(db, Sql2, -1, &stmt, NULL);
        count=0;
        while(sqlite3_step(stmt) ==SQLITE_ROW){

            int p0 = sqlite3_column_int(stmt,   0);
            int p1 = sqlite3_column_int(stmt,   1);
            double r0 = sqlite3_column_double(stmt,   2);
            double fc = sqlite3_column_double(stmt,   3);

            cout<<"Particle number "<<count<<"'s"<<" "<<"p0 number is "<<p0<<" "<<endl<<endl;//prints the p0 of the particle
            cout<<"Particle number "<<count<<"'s"<<" "<<"p1 number is "<<p1<<" "<<endl<<endl;//prints the p1 of the particle
            cout<<"Particle number "<<count<<"'s"<<" "<<"r0 number is "<<r0<<" "<<endl<<endl;//prints the r0 of the particle
            cout<<"Particle number "<<count<<"'s"<<" "<<"fc number is "<<fc<<" "<<endl<<endl;//prints the fc of the particle

            bonds->addBond(p0, p1, r0/10.0, 2*fc/1000.0);//adds bond and the arguements






            count++;




        }

            integrator.step(1);

            OpenMM::State state    = context.getState(OpenMM::State::Energy);//creates the energy
            double energy = state.getPotentialEnergy(); //gets the energy
            cout<<"The electrostatic energy of the system is "<<energy<<" "<<"kcal/mol"<<endl;//prints the electro static energy of the system


}
