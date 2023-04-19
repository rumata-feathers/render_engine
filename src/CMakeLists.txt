#message(engine_cmake_src_start)
set(PROJECT_SOURCES
        main.cpp
        interface.cpp
#        ${MW_SRC}
        ${LOGIC_SRC}
        ${main_window_SRC}
        )

message(STATUS ${MW_SRS})


add_executable(engine ${PROJECT_SOURCES})

target_link_libraries(engine PUBLIC ${QT_LIBRARIES})
target_link_libraries(engine PUBLIC Qt6::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
#target_link_libraries(engine PUBLIC ${MW_SRC})
#message(engine_cmake_src_finish)