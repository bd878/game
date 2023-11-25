cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(my-game LANGUAGES CXX)

add_executable(game main.cpp)

set_target_properties(game
  PROPERTIES
    CXX_STANDARD 14
    CXX_EXTENTIONS OFF
    CXX_STANDARD_REQUIRED ON
  )