cmake_minimum_required(VERSION 3.5)

project(SimpleCal VERSION 1.1.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

configure_file(
        "${PROJECT_SOURCE_DIR}/include/config.h.in"
        "${PROJECT_SOURCE_DIR}/include/config.h"
)

set(PROJECT_SOURCES
        main.cpp
        src/mainwindow.cc
        include/mainwindow.h
        src/ui/mainwindow.ui
        src/basic_cal_widget.cc
        include/basic_cal_widget.h
        src/ui/basic_cal_widget.ui
        src/percent_cal_widget.cc
        include/percent_cal_widget.h
        src/ui/percent_cal_widget.ui
        src/relative_cal_widget.cc
        include/relative_cal_widget.h
        src/ui/relative_cal_widget.ui
        src/utils.cc
        include/utils.h
        src/settings.cc
        include/settings.h
        include/config.h.in
        include/config.h
        src/settings_dialog.cc
        include/settings_dialog.h
        src/ui/settings_dialog.ui
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(SimpleCal
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
else ()
    if (ANDROID)
        add_library(SimpleCal SHARED
                ${PROJECT_SOURCES}
                )
    else ()
        add_executable(SimpleCal
                ${PROJECT_SOURCES}
                )
    endif ()
endif ()

# Windows下编译隐藏console
if (WIN32)
    if (MSVC)
        set_target_properties(SimpleCal PROPERTIES
                WIN32_EXECUTABLE YES
                LINK_FLAGS "/ENTRY:mainCRTStartup"
                )
    elseif (CMAKE_COMPILER_IS_GNUCXX)
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mwindows") # Not tested
    else ()
        message(SEND_ERROR "You are using an unsupported Windows compiler! (Not MSVC or GCC)")
    endif (MSVC)
elseif (APPLE)
    set_target_properties(SimpleCal PROPERTIES
            MACOSX_BUNDLE YES
            )
elseif (UNIX)
    # Nothing special required
else ()
    message(SEND_ERROR "You are on an unsupported platform! (Not Win32, Mac OS X or Unix)")
endif (WIN32)

target_link_libraries(SimpleCal PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(SimpleCal PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        )

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(SimpleCal)
endif ()
