cmake_minimum_required(VERSION 3.9)

project(qt-playlist VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS Multimedia REQUIRED)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Sql REQUIRED)

find_package(cpprestsdk REQUIRED) 

include_directories(include)
add_library(spotify
            src/spotify.cpp
            src/SpotifyClient.cpp)

set(PROJECT_SOURCES
        main.cpp
        include/rest.hpp
        include/widget.h
        src/widget.cpp
        src/widget.ui
        include/TokenManager.hpp
        src/TokenManager.cpp
        include/SpotifyClient.hpp
        src/SpotifyClient.cpp
        include/spotify.hpp
        src/spotify.cpp
        include/utils.hpp
        src/utils.cpp
        include/DatabaseManager.hpp
        src/DatabaseManager.cpp
        include/config.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(qt-playlist
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET qt-playlist APPEND PROPERTY QT_ANDROID_PACKAGE_SOURC0_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(qt-playlist SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(qt-playlist
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(qt-playlist PRIVATE 
                                  Qt::Widgets
                                  Qt::Sql
                                  Qt::Multimedia
                                  cpprestsdk::cpprest
                                  spotify)

set_target_properties(qt-playlist PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)


if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(qt-playlist)
endif()
