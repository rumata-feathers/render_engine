cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(MainWindow VERSION 0.1 LANGUAGES CXX)

set(MainWindow_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

message(${MainWindow_HEADER_DIR})
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(${MainWindow_HEADER_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)