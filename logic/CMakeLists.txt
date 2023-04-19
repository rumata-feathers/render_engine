cmake_minimum_required(VERSION 3.5)
project(logic VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LOGIC_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

include_directories(${LOGIC_HEADERS_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logic)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)