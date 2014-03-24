cmake_minimum_required(VERSION 2.8.9)

project(helloworld)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_MODULE_PATH /home/andrew/Qt/5.2.1/gcc_64/lib/cmake/Qt5Widgets)

# Find the QtWidgets library
find_package(Qt5Widgets)

# Tell CMake to create the helloworld executable
add_executable(helloworld main.cpp mainwindow.cpp)

# Use the Widgets module from Qt 5.
qt5_use_modules(helloworld Widgets)
