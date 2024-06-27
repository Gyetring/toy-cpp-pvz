cmake_minimum_required(VERSION 3.16)

add_library(
  Projectile
  STATIC
  Projectile.hpp
  Projectile.cpp
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
  Projectile
  Entity
  Interactive
  GameWorld
  GameObject
>>>>>>> refined
)

target_include_directories(
  Projectile
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
  ${CMAKE_SOURCE_DIR}/src/Entity/
  ${CMAKE_SOURCE_DIR}/src/Projectile/
)
>>>>>>> refined
