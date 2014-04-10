BeepHive
========

Swarm Robotics API and Simulator
## Running BeepHive
BeepHive is an MPI application and starts like any other:
```
$ mpirun -np $NUMPROCS BeepHive
```
Currently the parallel backend has not been completed so two processes should be
started, one for the GUI and one for the backend.
### Flags
|Flag|Abbreviation|Description|
|:----|:------|:-------------|
|`--nogui`|-n|Disables the GUI for a headless install|
## Build Instructions
### Make and enter build directory:
```
$ mkdir build
$ cd build
```
### Configure the build system
For normal builds something like this will be appropriate:
```
$ cmake -D CMAKE_CXX_COMPILER=mpicxx -D CMAKE_C_COMPILER=mpicc -D
Qt5Widgets_DIR=$QT_INSTALL_PATH/Qt/5.2.1/gcc_64/lib/cmake/Qt5Widgets ..
```

For builds on clusters or supercomputers where either Qt is not available or a
GUI simply will not be needed the GUI can be turned off at compile time with the
flag:
```
-D GUI=off
```
As a default GUI is on.
### Build the project
```
$ make
```
This will build both the library libBeep and the main BeepHive executable
### Build documetation
```
$ make doc
```
## Dependencies
###Boost
Make sure that Boost is installed, including:
* Boost-mpi: Boost-mpi simplifies the dirty work of mpi and makes developments
    of plugins easier

###Doxygen
We use Doxygen to generate documentation of our source code.
This is not necessary to get the project to build though

###pdflatex
If you would like to build a pdf of the documentation you will need pdflatex
