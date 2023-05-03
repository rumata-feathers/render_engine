set(PROJECT_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/logic.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../inc/logic.h
#        ${CMAKE_CURRENT_SOURCE_DIR}/testing.cpp
        ${BACK_LOGIC_SRC}
        )


set(LOGIC_SRC ${PROJECT_SOURCES} CACHE INTERNAL "")


add_executable(logic
        ${PROJECT_SOURCES}
        )
target_link_libraries(logic PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)