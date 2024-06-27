cmake_minimum_required(VERSION 3.16)

add_library(
  Interactive
  STATIC
  Interactive.hpp
  Interactive.cpp
)

target_link_libraries(
<<<<<<< HEAD
  GameObject
  Framework
  GameWorld
  Plant
  Zombie
  Interactive
  Projectile
=======
  Interactive
  GameWorld
  GameObject
>>>>>>> refined
)

target_include_directories(
  Interactive
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
<<<<<<< HEAD
  ${CMAKE_SOURCE_DIR}/src/GameWorld/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Plant/
  ${CMAKE_SOURCE_DIR}/src/Zombie/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
  ${CMAKE_SOURCE_DIR}/src/Projectile/
)
=======
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
)
>>>>>>> refined
