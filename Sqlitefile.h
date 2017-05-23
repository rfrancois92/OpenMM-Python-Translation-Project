#ifndef OPENMM_SQLITEFILE_H_
#define OPENMM_SQLITEFILE_H_

/* -------------------------------------------------------------------------- *
 *                                   OpenMM                                   *
 * -------------------------------------------------------------------------- *
 * This is part of the OpenMM molecular simulation toolkit originating from   *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
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
#include "openmm/Context.h"
#include <vector>
#include "internal/windowsSqlitefile.h"
#include <iostream>
#include <string>


using namespace std;

namespace SqlitefilePlugin {

/**
 * This class implements an anharmonic bond force of the form E(r)=k*(r-length)^4.  It exists to
 * serve as an example of how to write plugins.
 */

class OPENMM_EXPORT_EXAMPLE Sqlitefile {
public :
    /**
     * Create an ExampleForce.
     */
    Sqlitefile();
    /**
     * Get the number of bond stretch terms in the potential function
     */
    int Open(string filename) const;
private:
    OpenMM::System *system; //creates a new system

    OpenMM::HarmonicBondForce *bonds; //creates bonds

    OpenMM::NonbondedForce *nonbond;  //creates nonbonds
};


} // namespace Sqlitefileplugin

#endif /*OPENMM_SQLITEFILE_H_*/
