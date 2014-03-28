cmake_minimum_required(VERSION 2.6)
project(BeepHive)
set(BeepHive_VERSION_MAJOR 0)
set(BeepHive_VERSION_MINOR 0)

set(EXECUTABLE BeepHive)
set(LIBRARY Beep)
set(LIBRARY_TYPE SHARED)

set(BEEPHIVE_SOURCES
  src/BeepHiveConfigs.cpp
  src/BeepModel.cpp
  src/DiscreteTimeModel.cpp
  src/Event.cpp
  src/LightSensor.cpp
  src/Model.cpp
  src/SyncModel.cpp
  src/World.cpp
)

set(BEEPHIVE_HEADERS
  include/Beep.h
  include/BeepHive.h
  include/BeepHiveConfigs.h
  include/BeepModel.h
  include/DiscreteTimeModel.h
  include/Event.h
  include/Manipulator.h
  include/Model.h
  include/Sensor.h
  include/SyncModel.h
  include/World.h
)

set(BEEPHIVE_EXECUTABLE_SOURCES
  src/main.cpp
)

find_package(Boost COMPONENTS mpi REQUIRED)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${Boost_INCLUDE_DIR}
)

add_library(
  ${LIBRARY}
  ${LIBRARY_TYPE}
  ${BEEPHIVE_SOURCES}
  ${BEEPHIVE_HEADERS}
)
set_target_properties(
  ${LIBRARY}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY
  lib
)

add_executable(
  ${EXECUTABLE} 
  ${BEEPHIVE_EXECUTABLE_SOURCES}
)

target_link_libraries(
  ${EXECUTABLE}
  ${Boost_LIBRARIES} 
  ${LIBRARY}
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    DEPENDS ${EXECUTABLE}
    DEPENDS ${LIBRARY}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
  DEPENDS doc
  DEPENDS ${EXECUTABLE}
  DEPENDS ${LIBRARY}
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
  COMMAND make
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/latex
  COMMENT "Building LaTeX docs" VERBATIM
)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/manual.pdf
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
  COMMAND ${CMAKE_COMMAND} -E copy_if_different latex/refman.pdf manual.pdf
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(
  latex
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/manual.pdf
)

enable_testing()
add_test(mpi mpirun -np 2 ${CMAKE_CURRENT_BINARY_DIR}/${EXECUTABLE})
