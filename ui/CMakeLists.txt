# instead of automoc
# tell moc to manually run over headers
SET(CMAKE_AUTOMOC ON)
#qt_wrap_cpp(main_window_SRC ${UI_HEADER_DIR}/main_window.h)


#project resources
set(MAIN_WINDOW_PROJECT_SOURCES
        main_window.cpp
        main_window.h
        ui_main_window.h
        ../testing.cpp
#        ${main_window_SRC}
        ${LOGIC_SRC}
        )

#set(MW_ADD_SRC main_window.cpp)


# make visible to moc an any level
# (without it will catch error of missing vtable for MainWindow)
set(main_window_SRC ${main_window_SRC} CACHE INTERNAL "")
set(MW_SRS main_window.cpp CACHE INTERNAL "")

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(engine
            MANUAL_FINALIZATION
            ${MAIN_WINDOW_PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET engine APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(engine SHARED ${MAIN_WINDOW_PROJECT_SOURCES})
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(engine ${MAIN_WINDOW_PROJECT_SOURCES})
    endif ()
endif ()

set(QT_LIBRARIES Qt${QT_VERSION_MAJOR}::Widgets CACHE INTERNAL "")

target_link_libraries(engine PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(engine PUBLIC Qt6::OpenGL ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})

set_target_properties(engine PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )

install(TARGETS engine
        BUNDLE DESTINATION ../engine
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# project libraries
#get_target_property(MAIN_WINDOW_LIBRARIES engine LINK_LIBRARIES)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(engine)
endif ()
