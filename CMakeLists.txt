cmake_minimum_required(VERSION 2.8.9)
project(BeepHive)
set(BeepHive_VERSION_MAJOR 0)
set(BeepHive_VERSION_MINOR 0)

#Build types:
option(GUI "GUI" ON)
if(GUI)
  add_definitions(-DGUI)
endif(GUI)

set(CMAKE_CXX_FLAGS " -std=c++0x -Wall"
    CACHE STRING "" FORCE)


# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(LIBRARY_TYPE SHARED)

set(EXECUTABLE BeepHive)
set(LIB_BEEP Beep)
set(LIB_PLUGIN BeepPlugin)

if(GUI)
  set(LIB_GUI BeepGui)
endif(GUI)


set(BEEPHIVE_HEADERS
  Beep/include/Beep.h
  Beep/include/BeepHiveConfigs.h
  Beep/include/BeepLayer.h
  Beep/include/BoundaryValues.h
  Beep/include/CentralCommunicator.h
  Beep/include/Command.h
  Beep/include/Communicator.h
  Beep/include/Controller.h
  Beep/include/CustomBeepFactory.h
  Beep/include/DataPoint.h
  Beep/include/Dealii.h
  Beep/include/DiscreteTimeLayer.h
  Beep/include/EnvObject.h
  Beep/include/Event.h
  Beep/include/Factory.h
  Beep/include/FileCommunicator.h
  Beep/include/InitialValues.h
  Beep/include/Layer.h
  Beep/include/LoadCommand.h
  Beep/include/Manipulator.h
  Beep/include/Pattern.h
  Beep/include/RightHandSide.h
  Beep/include/Sensor.h
  Beep/include/Serializable.h
  Beep/include/Singleton.h
  Beep/include/Stateful.h
  Beep/include/SyncLayer.h
  Beep/include/World.h
)

set(BEEPHIVE_SOURCES
  Beep/src/Beep.cpp
  Beep/src/BeepHiveConfigs.cpp
  Beep/src/BeepLayer.cpp
  Beep/src/CentralCommunicator.cpp
  Beep/src/Command.cpp
  Beep/src/Communicator.cpp
  Beep/src/CustomBeepFactory.cpp
  Beep/src/DataPoint.cpp
  Beep/src/DiscreteTimeLayer.cpp
  Beep/src/EnvObject.cpp
  Beep/src/Event.cpp
  Beep/src/FileCommunicator.cpp
  Beep/src/Manipulator.cpp
  Beep/src/Layer.cpp
  Beep/src/LoadCommand.cpp
  Beep/src/Pattern.cpp
  Beep/src/Serializable.cpp
  Beep/src/Stateful.cpp
  Beep/src/SyncLayer.cpp
  Beep/src/World.cpp
)

set(PLUGIN_HEADERS
  Plugin/include/AverageSensor.h
  Plugin/include/BasicController.h
  Plugin/include/FlockingController.h
  Plugin/include/HeatEquation.h
  Plugin/include/HeatLayer.h
  Plugin/include/HeatSensor.h
  Plugin/include/LightSensor.h
  Plugin/include/OmegaVelocityManipulator.h
  Plugin/include/RectanglePattern.h
)

set(PLUGIN_SOURCES
  Plugin/src/AverageSensor.cpp
  Plugin/src/BasicController.cpp
  Plugin/src/FlockingController.cpp
  Plugin/src/HeatLayer.cpp
  Plugin/src/HeatSensor.cpp
  Plugin/src/LightSensor.cpp
  Plugin/src/OmegaVelocityManipulator.cpp
  Plugin/src/RectanglePattern.cpp
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
    GUI/include/newbeeptype.h
  )

  set(GUI_SOURCES
    GUI/src/mainwindow.cpp
    GUI/src/robot.cpp
    GUI/src/debugwindow.cpp
    GUI/src/createagent.cpp
    GUI/src/createenvironment.cpp
    GUI/src/environmentobject.cpp
    GUI/src/newbeeptype.cpp
  )
endif(GUI)

set(BEEPHIVE_EXECUTABLE_SOURCES
  Beep/src/main.cpp
)

find_package(Boost COMPONENTS mpi serialization REQUIRED)

find_package(deal.II 8.0 REQUIRED
  HINTS ${deal.II_DIR} ${DEAL_II_DIR} ../ ../../ $ENV{DEAL_II_DIR}
  )
#deal_ii_initialize_cached_variables()

if(GUI)
  find_package(Qt5Widgets)
endif(GUI)

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Beep/include
  ${CMAKE_CURRENT_SOURCE_DIR}/Plugin/include
  ${CMAKE_CURRENT_SOURCE_DIR}/GUI/include
  ${Boost_INCLUDE_DIR}
)

add_library(
  ${LIB_BEEP}
  ${LIBRARY_TYPE}
  ${BEEPHIVE_SOURCES}
  ${BEEPHIVE_HEADERS}
)
set_target_properties(
  ${LIB_BEEP}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY
  lib
)
target_link_libraries(
  ${LIB_BEEP}
  ${Boost_LIBRARIES} 
)

add_library(
  ${LIB_PLUGIN}
  ${LIBRARY_TYPE}
  ${PLUGIN_SOURCES}
  ${PLUGIN_HEADERS}
)
deal_ii_setup_target(${LIB_PLUGIN})
set_target_properties(
  ${LIB_PLUGIN}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY
  lib
)
target_link_libraries(
  ${LIB_PLUGIN}
  ${LIB_BEEP}
)
get_property(PLUGIN_LOCATION TARGET ${LIB_PLUGIN} PROPERTY LOCATION)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Beep/include/BeepHive.h.in
  ${CMAKE_CURRENT_BINARY_DIR}/include/BeepHive.h @ONLY)

if(GUI)
  add_library(
    ${LIB_GUI}
    ${LIBRARY_TYPE}
    ${GUI_SOURCES}
    ${GUI_HEADERS}
  )
  set_target_properties(
    ${LIB_GUI}
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY
    lib
  )
  target_link_libraries(
    ${LIB_GUI}
    ${LIB_BEEP}
    )
endif(GUI)

add_executable(
  ${EXECUTABLE} 
  ${BEEPHIVE_EXECUTABLE_SOURCES}
)
target_link_libraries(
  ${EXECUTABLE}
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
  ${LIB_GUI}
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

target_link_libraries(
  BackendTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
)

add_executable(
  JSONTest
  test/JSON_test.cpp
)

target_link_libraries(
  JSONTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
)

add_executable(
  CommandsTest
  test/commands_test.cpp
)

target_link_libraries(
  CommandsTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
)

add_executable(
  StressTest
  test/stress_test.cpp
)

target_link_libraries(
  StressTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
)

add_executable(
  LoadTest
  test/load_test.cpp
)

target_link_libraries(
  LoadTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
)
add_executable(
  HeatTest
  test/heat_test.cpp
)

target_link_libraries(
  HeatTest
  ${Boost_LIBRARIES} 
  ${LIB_BEEP}
  ${LIB_PLUGIN}
)

if(GUI)
  add_executable(
    GuiTest
    GUI/src/main.cpp
  )
  target_link_libraries(
    GuiTest
    ${Boost_LIBRARIES} 
    ${LIB_BEEP}
    ${LIB_GUI}
  )
endif(GUI)

enable_testing()
add_test(commands ${CMAKE_CURRENT_BINARY_DIR}/CommandsTest)
add_test(stress ${CMAKE_CURRENT_BINARY_DIR}/StressTest)
add_test(JSON ${CMAKE_CURRENT_BINARY_DIR}/JSONTest)
add_test(backend mpirun -np 2 ${CMAKE_CURRENT_BINARY_DIR}/BackendTest)
add_test(load ${CMAKE_CURRENT_BINARY_DIR}/LoadTest lib/lib${LIB_PLUGIN}.so)
add_test(heat ${CMAKE_CURRENT_BINARY_DIR}/HeatTest)

if(GUI)
  qt5_use_modules(GuiTest Widgets)
  qt5_use_modules(${LIB_GUI} Widgets)
  qt5_use_modules(${EXECUTABLE} Widgets)
endif(GUI)

install(TARGETS ${EXECUTABLE} ${LIB_BEEP} ${LIB_PLUGIN} ${LIB_GUI}
  RUNTIME DESTINATION /usr/local/bin
  LIBRARY DESTINATION /usr/local/lib
  ARCHIVE DESTINATION /usr/local/lib
)
  
