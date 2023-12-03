cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(my-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXTENSIONS OFF)
set(CMAKE_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")
list(APPEND flags "-Wall")

find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
  message(STATUS "SDL2 found")
else()
  message(STATUS "SDL2 not found")
endif()

add_library(
  InputHandler
  InputHandler.cpp
  InputHandler.h
)

add_library(
  Game
  Game.h
  Game.cpp
  Square.h
  Square.cpp
  Vector2D.cpp
  Vector2D.h
  GameObject.h
)

add_executable(game main.cpp)
target_link_libraries(game SDL2 Game InputHandler)
