cmake_minimum_required(VERSION 2.8.9)

project(helloworld)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

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
  src/main.cpp
  src/mainwindow.cpp
  src/robot.cpp
  src/debugwindow.cpp
)


INCLUDE_DIRECTORIES(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Tell CMake to create the helloworld executable
add_executable(helloworld
  ${GUI_SOURCES}
  ${GUI_HEADERS}
)

# Use the Widgets module from Qt 5.
qt5_use_modules(helloworld Widgets)
