cmake_minimum_required(VERSION 3.16)

add_library(
  Interactive
  STATIC
  Interactive.hpp
  Interactive.cpp
)

target_link_libraries(
  GameObject
  Framework
  GameWorld
)

target_include_directories(
  Interactive
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
)
