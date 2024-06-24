cmake_minimum_required(VERSION 3.16)

add_library(
  Plant
  STATIC
  Plant.hpp
  Plant.cpp
)

target_link_libraries(
  GameObject
  Plant
  Framework
  GameWorld
  Interactive
  Zombie
  Projectile
)

target_include_directories(
  Plant
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
  ${CMAKE_SOURCE_DIR}/src/Plant/
  ${CMAKE_SOURCE_DIR}/src/Zombie/
  ${CMAKE_SOURCE_DIR}/src/Projectile/
)
