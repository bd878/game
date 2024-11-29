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

find_package(SDL2_image REQUIRED)
if(SDL2_FOUND)
  message(STATUS "SDL2_image found")
else()
  message(STATUS "SDL2_image not found")
endif()

find_package(SDL2_mixer REQUIRED)
if(SDL2_mixer_FOUND)
  message(STATUS "SDL2_mixer found")
else()
  message(STATUS "SDL2_mixer not found")
endif()

find_package(ZLIB REQUIRED)
if(ZLIB_FOUND)
  message(STATUS "Zlib found")
else()
  message(STATUS "Zlib not found")
endif()

add_library(
  Sound
  SoundManager.h
  SoundManager.cpp
)

add_library(
  Tinyxml
  tinyxml2.h
  tinyxml2.cpp
)

add_library(
  base64
  base64.h
  base64.cpp
)

add_library(
  Layers
  Layer.h
  ObjectLayer.h
  ObjectLayer.cpp
  TileLayer.h
  TileLayer.cpp
  LevelParser.h
  LevelParser.cpp
  Level.h
  Level.cpp
)

add_library(
  InputHandler
  InputHandler.cpp
  InputHandler.h
  LoaderParams.h
)

add_library(
  Collisions
  Collisions.h
  CollisionManager.cpp
  CollisionManager.h
)

add_library(
  GameObjects
  BulletHandler.cpp
  BulletHandler.h
  EnemyBullet.h
  PlayerBullet.h
  GameObject.h
  Player.h
  Player.cpp
  Enemy.h
  Enemy.cpp
  ShooterObject.h
  ShooterObject.cpp
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
  MainMenuState.cpp
  MainMenuState.h
  GameOverState.h
  GameOverState.cpp
  PlayState.h
  PlayState.cpp
  GameStateMachine.h
  GameStateMachine.cpp
  PauseState.h
  PauseState.cpp
  GameObjectFactory.h
  GameObjectFactory.cpp
  StateParser.cpp
  StateParser.h
)

add_library(
  Game
  Game.h
  Game.cpp
  Vector2D.h
)

target_link_libraries(GameStates TextureManager GameObjects base64)

target_link_libraries(Game PUBLIC SDL2 SDL2_image SDL2_mixer z)

add_executable(game main.cpp)
target_link_libraries(
  game
  SDL2
  SDL2_image
  SDL2_mixer
  Sound
  Game
  Collisions
  GameObjects
  InputHandler
  GameStates
  TextureManager
  Tinyxml
  Layers
)
