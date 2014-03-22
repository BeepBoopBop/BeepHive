BeepHive
========

Swarm Robotics API and Simulator

## Build Instructions
### Make and enter build directory:
```
$ mkdir build
$ cd build
```
### Configure the build system
```
$ cmake -D CMAKE_CXX_COMPILER=mpicxx -D CMAKE_C_COMPILER=mpicc ..
```
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
