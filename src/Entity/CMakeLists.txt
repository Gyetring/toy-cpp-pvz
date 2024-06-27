cmake_minimum_required(VERSION 3.16)

add_library(
  Entity
  STATIC
  Entity.hpp
  Entity.cpp
)

target_link_libraries(
  Entity
  Interactive
  GameWorld
  GameObject
)

target_include_directories(
  Entity
  PUBLIC 
  ${CMAKE_SOURCE_DIR}/src/
  ${CMAKE_SOURCE_DIR}/src/Framework/
  ${CMAKE_SOURCE_DIR}/src/GameObject/
  ${CMAKE_SOURCE_DIR}/src/Interactive/
  ${CMAKE_SOURCE_DIR}/src/Entity/
)