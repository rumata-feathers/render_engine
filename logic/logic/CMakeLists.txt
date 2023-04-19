cmake_minimum_required(VERSION 3.5)
project(back_logic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(BACK_LOGIC_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${BACK_LOGIC_HEADERS_DIR})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)