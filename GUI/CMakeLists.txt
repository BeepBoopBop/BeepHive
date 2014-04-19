cmake_minimum_required(VERSION 2.8.9)

project(helloworld)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

set(LIB_BEEPGUI BeepGui)
set(LIBRARY_TYPE SHARED)

# Find the QtWidgets library
find_package(Qt5Widgets)

set(GUI_HEADERS
  include/gui_includes.h
  include/mainwindow.h
  include/robot.h
  include/ui_mainwindow.h
  include/ui_debugwindow.h
  include/debugwindow.h
)
set(GUI_SOURCES
  src/mainwindow.cpp
  src/robot.cpp
  src/debugwindow.cpp
)



INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
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

# Tell CMake to create the helloworld executable
add_executable(
  GuiTest
  src/main.cpp
)
target_link_libraries(
  GuiTest
  ${LIB_BEEPGUI}
)

# Use the Widgets module from Qt 5.
qt5_use_modules(GuiTest Widgets)
qt5_use_modules(${LIB_BEEPGUI} Widgets)
