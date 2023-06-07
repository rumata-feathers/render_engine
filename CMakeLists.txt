cmake_minimum_required(VERSION 3.5)

project(engine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH "/opt/homebrew/opt")

set(ENGINE_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(UI_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ui)
set(QT_PREFIX ${/opt/homebrew/opt})

include_directories(${ENGINE_HEADER_DIR})
include_directories(${UI_HEADER_DIR})
include_directories(${QT_PREFIX})

find_package(OpenGL REQUIRED)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

#target_link_libraries(engine PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/ui)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/logic)

#add_executable(engine testing.cpp)

