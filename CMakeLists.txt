cmake_minimum_required(VERSION 2.6)
project(BeepHive)
set(BeepHive_VERSION_MAJOR 0)
set(BeepHive_VERSION_MINOR 0)

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
)

#SOURCES ${BEEPHIVE_SOURCES}
#HEADERS ${BEEPHIVE_HEADERS}
#DEFINES ${BEEPHIVE_DEFS}
INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(BeepHive 
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
