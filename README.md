# OpenMM SQL Interface plugin

*** WORK IN PROGRESS ***

A plugin that finds the electrostatic energy of the system using SQL and C++ code.

Name E-mail Reginald Francois
Last Modified: May 2017


## License

This software is released under the LGPL license

## Credits



The plugin interface is based on the [openm_Sqlitefile_plugin] (https://github.com/rfrancois92/OpenMM_SQL_Interface.git) by Reginald Francois.

## Installation

These instructions assume Linux. Install OpenMM 7; the easiest is through `miniconda` using [these instructions](https://simtk.org/frs/download_start.php/file/4907/Conda%20installation%20instruction?group_id=161). Install `swig` through `conda` as well:

```
conda install -c omnia openmm swig
```

Locate the OpenMM installation directory, otherwise it will default to `/usr/local/openmm`. If OpenMM was installed via `conda` the OpenMM installation directory will be something like `$HOME/miniconda2/pkgs/openmm-7.0.1-py27_0`

Download this plugin package from github:

```
git clone https://github.com/rfrancois92/OpenMM_SQL_Interface.git
```

Build and install the plugin with cmake. For example, assuming a unix system and a `conda` environment:
```
. ~/miniconda2/bin/activate
mkdir build_openmm_..._plugin
cd build_openmm_..._plugin
ccmake -i ../openmm_..._plugin
```

Hit `c` (configure) until all variables are correctly set, then `g` to generate the makefiles. `OPENMM_DIR` should point to the OpenMM installation directory. `CMAKE_INSTALL_PREFIX` normally is the same as `OPENMM_DIR`. 

Once the configuration is done do:

```
make
make install
```

The last two steps may need superuser access depending on the installation target, or use the recommended `conda` environment.

## Test

`cd` to the directory where you cloned the `https://github.com/rfrancois92/OpenMM_SQL_Interface.git` sources. Then:

```
 cd build_openmm_sqlitefile_plugin/
 cd platforms/reference/tests/
 ./TestReferenceSqlitefile 


where `<openmm_dir>` is the OpenMM installation directory.


