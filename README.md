# OpenMM SQL Interface plugin

*** WORK IN PROGRESS ***

A plugin that ...

Name E-mail
Last Modified:


## License

This software is released under the LGPL license

## Credits



The plugin interface is based on the [openmmexampleplugin](https://github.com/peastman/openmmexampleplugin) by Peter Eastman.

## Installation

These instructions assume Linux. Install OpenMM 7; the easiest is through `miniconda` using [these instructions](https://simtk.org/frs/download_start.php/file/4907/Conda%20installation%20instruction?group_id=161). Install `swig` through `conda` as well:

```
conda install -c omnia openmm swig
```

Locate the OpenMM installation directory, otherwise it will default to `/usr/local/openmm`. If OpenMM was installed via `conda` the OpenMM installation directory will be something like `$HOME/miniconda2/pkgs/openmm-7.0.1-py27_0`

Download this plugin package from github:

```
git clone https://github.com/....git
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

`cd` to the directory where you cloned the `openmm_..._plugin` sources. Then:

```
cd example
export OPENMM_PLUGIN_DIR=<openmm_dir>/lib/plugins
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:<openmm_dir>/lib:<openmm_dir>lib/plugins
./Test...
```

where `<openmm_dir>` is the OpenMM installation directory.


