cmake_minimum_required(VERSION 3.16)

add_library(
  Projectile
  STATIC
  Projectile.hpp
  Projectile.cpp
)

target_link_libraries(
  Projectile
  Entity
  Interactive
  GameWorld
  GameObject
)

target_include_directories(
  Projectile
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
  ${CMAKE_SOURCE_DIR}/src/Entity/
  ${CMAKE_SOURCE_DIR}/src/Projectile/
)