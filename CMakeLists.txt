cmake_minimum_required(VERSION 3.22)
project(golf)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(golf
        Background.cpp
        Background.h
        Ball.cpp
        Ball.h
        Entity.cpp
        Entity.h
        FirstItem.h
        Hole.cpp
        Hole.h
        Imagens.cpp
        Launcher.cpp
        Launcher.h
        Level.cpp
        Level.h
        Obstacle.cpp
        Obstacle.h
        Origem.cpp
        Screen.cpp
        Screen.h
        Timer.h
        Timer.cpp util/Util.cpp util/Util.hpp util/Consts.hpp)
target_link_libraries(${PROJECT_NAME} SDL2::Main SDL2::TTF SDL2::Image)
