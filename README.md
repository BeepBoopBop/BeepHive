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
|:----------------|:------|:-------------|
|`--nogui`        |-n|Disables the GUI|
|`--input <file>` |-i|Load file for input|
|`--output <file>`|-o|Load file for output|
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

###CMake
This project uses CMake 2.8.9 because this is required by Qt.
This version of CMake is likely newer than what is included in repositories,
downloading a newer version from www.cmake.org may be necessary

###Deal.II
Library to solve PDE's download from here http://www.dealii.org/

Using version 8.1.0 unpack with:
```
tar -xvf deal.II-8.1.0.tar.gz
```
Install using the following commands:
```
$ mkdir build
$ cd build
$ cmake -DCMAKE_INSTALL_PREFIX=/path/to/install/dir -DDEAL_II_WITH_THREADS=OFF -DDEAL_II_WITH_MPI=ON ..
$ make
$ make install
$ make test
```
Be sure that MPI is flagged on otherwise it might not link properly.
If you have root permissions you can just set the install path to /usr/local.

The make test command will ensure that it installed properly (You should see 100% of tests passed).

###Doxygen
We use Doxygen to generate documentation of our source code.
This is not necessary to get the project to build though

###pdflatex
If you would like to build a pdf of the documentation you will need pdflatex

###Qt
Qt 5.2 is required to build the GUI library. This can be found at qt-project.org
