cmake_minimum_required(VERSION 3.9)
project(qt-playlist)

find_package(cpprestsdk REQUIRED)

## Compile as C++17
add_compile_options(-std=c++17)

include_directories(include)

add_library(spotify
            src/spotify.cpp
            src/SpotifyClient.cpp)

add_executable(main main.cpp)
target_link_libraries(main 
                      PRIVATE cpprestsdk::cpprest spotify)