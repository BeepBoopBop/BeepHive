cmake_minimum_required(VERSION 2.8.9)
project(BeepHive)
set(BeepHive_VERSION_MAJOR 0)
set(BeepHive_VERSION_MINOR 0)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(EXECUTABLE BeepHive)
set(LIB_BEEP Beep)
set(LIB_BEEPGUI BeepGui)
set(LIBRARY_TYPE SHARED)

set(BEEPHIVE_HEADERS
  include/Beep.h
  include/BeepHive.h
  include/BeepHiveConfigs.h
  include/BeepLayer.h
  include/DiscreteTimeLayer.h
  include/Event.h
  include/Manipulator.h
  include/Layer.h
  include/OmegaVelocityManipulator.h
  include/Sensor.h
  #include/Serializeable.h
  include/SyncLayer.h
  include/World.h
)

set(BEEPHIVE_SOURCES
  src/Beep.cpp
  src/BeepHiveConfigs.cpp
  src/BeepLayer.cpp
  src/DiscreteTimeLayer.cpp
  src/Event.cpp
  src/LightSensor.cpp
  src/Manipulator.cpp
  src/Layer.cpp
  src/OmegaVelocityManipulator.cpp
  #src/Serializeable.cpp
  src/SyncLayer.cpp
  src/World.cpp
)

set(GUI_HEADERS
  GUI/include/gui_includes.h
  GUI/include/mainwindow.h
  GUI/include/robot.h
  GUI/include/ui_mainwindow.h
  GUI/include/ui_debugwindow.h
  GUI/include/debugwindow.h
)

set(GUI_SOURCES
  GUI/src/mainwindow.cpp
  GUI/src/robot.cpp
  GUI/src/debugwindow.cpp
)

set(BEEPHIVE_EXECUTABLE_SOURCES
  src/main.cpp
)

find_package(Boost COMPONENTS mpi serialization REQUIRED)
find_package(Qt5Widgets)

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
set_target_properties(
  ${LIB_BEEP}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY
  lib
)

add_library(
  ${LIB_BEEPGUI}
  ${LIBRARY_TYPE}
  ${GUI_SOURCES}
  ${GUI_HEADERS}
)
set_target_properties(
  ${LIB_BEEPGUI}
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
  ${LIB_BEEP}
  ${LIB_BEEPGUI}
)

# add a target to generate API documentation with Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
    DEPENDS ${EXECUTABLE}
    DEPENDS ${LIB_BEEP}
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile 
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/header.tex 
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
endif(DOXYGEN_FOUND)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/latex/refman.pdf
  DEPENDS doc
  DEPENDS ${EXECUTABLE}
  DEPENDS ${LIB_BEEP}
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
  GuiTest
  GUI/src/main.cpp
)
target_link_libraries(
  GuiTest
  ${LIB_BEEPGUI}
  ${Boost_LIBRARIES} 
)

enable_testing()
add_test(mpi mpirun -np 2 ${CMAKE_CURRENT_BINARY_DIR}/BackendTest)

qt5_use_modules(GuiTest Widgets)
qt5_use_modules(${LIB_BEEPGUI} Widgets)
qt5_use_modules(${EXECUTABLE} Widgets)
