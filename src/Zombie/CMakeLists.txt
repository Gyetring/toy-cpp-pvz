cmake_minimum_required(VERSION 3.16)

add_library(
  Zombie
  STATIC
  Zombie.hpp
  Zombie.cpp
)

target_link_libraries(
  GameObject
  Plant
  Framework
  GameWorld
  Interactive
  Zombie
)

target_include_directories(
  Zombie
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
  ${CMAKE_SOURCE_DIR}/src/Zombie/
  ${CMAKE_SOURCE_DIR}/src/Plant/
)
