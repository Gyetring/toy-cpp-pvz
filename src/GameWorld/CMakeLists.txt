cmake_minimum_required(VERSION 3.16)

add_library(
  GameWorld
  STATIC
  GameWorld.hpp
  GameWorld.cpp
)

target_link_libraries(
  GameWorld
  GameObject
  Interactive
  Plant
  Zombie
)

target_include_directories(
  GameWorld
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
  ${CMAKE_SOURCE_DIR}/src/Plant/
  ${CMAKE_SOURCE_DIR}/src/Zombie/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
)
