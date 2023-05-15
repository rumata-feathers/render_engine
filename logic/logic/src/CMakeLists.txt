set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Scene.cpp
#        ${CMAKE_CURRENT_SOURCE_DIR}/testing.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ray.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/camera.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/hittable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sphere.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/hittable_list.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/vec3.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/material.cpp)
set(BACK_LOGIC_SRC ${PROJECT_SOURCES} CACHE INTERNAL "")

add_executable(back_logic ${PROJECT_SOURCES})