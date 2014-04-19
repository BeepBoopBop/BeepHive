cmake_minimum_required(VERSION 2.8.9)
project(BeepHive)
set(BeepHive_VERSION_MAJOR 0)
set(BeepHive_VERSION_MINOR 0)

#Build types:
option(GUI "GUI" ON)
if(GUI)
  add_definitions(-DGUI)
endif(GUI)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall -Wextra"
    CACHE STRING "" FORCE)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(EXECUTABLE BeepHive)
set(LIB_BEEP Beep)

if(GUI)
  set(LIB_BEEPGUI BeepGui)
  set(LIBRARY_TYPE SHARED)
endif(GUI)


set(BEEPHIVE_HEADERS
  include/AverageSensor.h
  include/BasicController.h
  include/Beep.h
  include/BeepHive.h
  include/BeepHiveConfigs.h
  include/BeepLayer.h
  include/Controller.h
  include/CustomBeepFactory.h
  include/Dealii.h
  include/DiscreteTimeLayer.h
  include/Event.h
  include/Factory.h
  include/FlockingController.h
  include/HeatEquation.h
  include/HeatLayer.h
  include/Layer.h
  include/LightSensor.h
  include/Manipulator.h
  include/OmegaVelocityManipulator.h
  include/Sensor.h
  include/Serializeable.h
  include/SyncLayer.h
  include/World.h
)

set(BEEPHIVE_SOURCES
  src/AverageSensor.cpp
  src/BasicController.cpp
  src/Beep.cpp
  src/BeepHiveConfigs.cpp
  src/BeepLayer.cpp
  src/CustomBeepFactory.cpp
  src/DiscreteTimeLayer.cpp
  src/Event.cpp
  src/FlockingController.cpp
  src/HeatLayer.cpp
  src/LightSensor.cpp
  src/Manipulator.cpp
  src/Layer.cpp
  src/OmegaVelocityManipulator.cpp
  src/Serializeable.cpp
  src/SyncLayer.cpp
  src/World.cpp
)

if(GUI)
  set(GUI_HEADERS
    GUI/include/createagent.h
    GUI/include/gui_includes.h
    GUI/include/mainwindow.h
    GUI/include/robot.h
    GUI/include/ui_mainwindow.h
    GUI/include/ui_debugwindow.h
    GUI/include/debugwindow.h
    GUI/include/createenvironment.h
    GUI/include/environmentobject.h
    GUI/include/ui_createagent.h
    GUI/include/ui_createenvironment.h
  )

  set(GUI_SOURCES
    GUI/src/mainwindow.cpp
    GUI/src/robot.cpp
    GUI/src/debugwindow.cpp
    GUI/src/createagent.cpp
    GUI/src/createenvironment.cpp
    GUI/src/environmentobject.cpp
  )
endif(GUI)

set(BEEPHIVE_EXECUTABLE_SOURCES
  src/main.cpp
)

find_package(Boost COMPONENTS mpi serialization REQUIRED)

find_package(deal.II 8.0 REQUIRED
  HINTS ${deal.II_DIR} ${DEAL_II_DIR} ../ ../../ $ENV{DEAL_II_DIR}
  )
deal_ii_initialize_cached_variables()

if(GUI)
  find_package(Qt5Widgets)
endif(GUI)

INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include
  ${Boost_INCLUDE_DIR}
)

add_library(
  ${LIB_BEEP}
  ${LIBRARY_TYPE}
  ${BEEPHIVE_SOURCES}
  ${BEEPHIVE_HEADERS}
)
deal_ii_setup_target(${LIB_BEEP})
set_target_properties(
  ${LIB_BEEP}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY
  lib
)

if(GUI)
  add_library(
    ${LIB_BEEPGUI}
    ${LIBRARY_TYPE}
    ${GUI_SOURCES}
    ${GUI_HEADERS}
  )
  deal_ii_setup_target(${LIB_BEEPGUI})
  set_target_properties(
    ${LIB_BEEPGUI}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    lib
  )
endif(GUI)

add_executable(
  ${EXECUTABLE} 
  ${BEEPHIVE_EXECUTABLE_SOURCES}
)
deal_ii_setup_target(${EXECUTABLE})

target_link_libraries(
  ${EXECUTABLE}
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
  ${LIB_BEEPGUI}
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    DEPENDS ${GUI_SOURCES}
    DEPENDS ${GUI_HEADERS}
    DEPENDS ${BEEPHIVE_SOURCES}
    DEPENDS ${BEEPHIVE_HEADERS}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/header.tex 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
  DEPENDS doc
  DEPENDS ${GUI_SOURCES} DEPENDS ${GUI_HEADERS}
  DEPENDS ${BEEPHIVE_SOURCES}
  DEPENDS ${BEEPHIVE_HEADERS}
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/header.tex 
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

# TESTING
add_executable(
  BackendTest
  test/backend_test.cpp
)
deal_ii_setup_target(BackendTest)

target_link_libraries(
  BackendTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
)

if(GUI)
  add_executable(
    GuiTest
    GUI/src/main.cpp
  )
  deal_ii_setup_target(GuiTest)
  target_link_libraries(
    GuiTest
    ${LIB_BEEPGUI}
    ${Boost_LIBRARIES} 
  )
endif(GUI)

enable_testing()
add_test(mpi mpirun -np 2 ${CMAKE_CURRENT_BINARY_DIR}/BackendTest)

if(GUI)
  qt5_use_modules(GuiTest Widgets)
  qt5_use_modules(${LIB_BEEPGUI} Widgets)
  qt5_use_modules(${EXECUTABLE} Widgets)
endif(GUI)
