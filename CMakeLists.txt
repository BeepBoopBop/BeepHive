cmake_minimum_required(VERSION 2.6)
project(BeepHive)
set(BeepHive_VERSION_MAJOR 0)
set(BeepHive_VERSION_MINOR 0)

set(EXECUTABLE BeepHive)

set(BEEPHIVE_SOURCES
  src/DiscreteTimeModel.cpp
  src/Event.cpp
  src/main.cpp
  src/Model.cpp
)

set(BEEPHIVE_HEADERS
  include/DiscreteTimeModel.h
  include/Event.h
  include/Model.h
  include/World.h
  include/BeepModel.h
  include/Beep.h
)

#SOURCES ${BEEPHIVE_SOURCES}
#HEADERS ${BEEPHIVE_HEADERS}
#DEFINES ${BEEPHIVE_DEFS}
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(${EXECUTABLE} 
               ${BEEPHIVE_SOURCES}
              )

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
  DEPENDS doc
  COMMAND make
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
  COMMENT "Building LaTeX docs" VERBATIM
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/manual.pdf
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
  COMMAND ${CMAKE_COMMAND} -E copy latex/refman.pdf manual.pdf
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(
  latex
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/manual.pdf
)

enable_testing()
add_test(mpi mpirun -np 2 ${EXECUTABLE})
