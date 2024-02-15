cmake_minimum_required(VERSION 3.22)
project(menu)

set(CMAKE_CXX_STANDARD 14)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)


include_directories(${SDL2_INCLUDE_DIRS})
add_executable(menu main.cpp components/Button.cpp components/Button.hpp)

target_link_libraries(menu SDL2::Main SDL2::TTF )