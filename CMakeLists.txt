cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(my-game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXTENSIONS OFF)
set(CMAKE_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

message("C++ compiler flags: ${CMAKE_CXX_FLAGS}")
list(APPEND flags "-Wall")

find_package(SDL2 REQUIRED COMPONENTS SDL2_image)
if(SDL2_FOUND)
  message(STATUS "SDL2 found with libraries")
else()
  message(STATUS "SDL2 not found")
endif()

add_library(
  InputHandler
  InputHandler.cpp
  InputHandler.h
  LoaderParams.h
)

add_library(
  GameObjects
  GameObject.h
  Player.h
  Player.cpp
  Enemy.h
  Enemy.cpp
  AnimatedObject.h
  AnimatedObject.cpp
  AnimatedGraphic.h
  AnimatedGraphic.cpp
  MenuButton.h
  MenuButton.cpp
)

add_library(
  TextureManager
  TextureManager.h
  TextureManager.cpp
)

add_library(
  GameStates
  GameState.h
  MenuState.h
  MenuState.cpp
  GameOverState.h
  GameOverState.cpp
  PlayState.h
  PlayState.cpp
  GameStateMachine.h
  GameStateMachine.cpp
  PauseState.h
  PauseState.cpp
)

add_library(
  Game
  Game.h
  Game.cpp
  Vector2D.h
)

target_link_libraries(GameStates TextureManager GameObjects)

target_link_libraries(Game PUBLIC SDL2 SDL2_image)

add_executable(game main.cpp)
target_link_libraries(game SDL2 SDL2_image Game GameObjects InputHandler GameStates TextureManager)
