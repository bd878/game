cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(my-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXTENSIONS OFF)
set(CMAKE_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
  message(STATUS "SDL2 found")
else()
  message(STATUS "SDL2 not found")
endif()

add_library(Game Game.cpp)

add_executable(game main.cpp)
target_link_libraries(game SDL2 Game)
