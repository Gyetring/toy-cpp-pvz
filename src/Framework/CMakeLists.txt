cmake_minimum_required(VERSION 3.16)

IF(APPLE)
    add_definitions(-DGL_SILENCE_DEPRECATION)
ENDIF()

set(FREEGLUT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/freeglut/include")

add_library(
  Framework
  STATIC
  ObjectBase.hpp
  ObjectBase.cpp
  WorldBase.hpp
  WorldBase.cpp
  TextBase.hpp
  TextBase.cpp
  GameManager.hpp
  GameManager.cpp
  SpriteManager.hpp
  SpriteManager.cpp
  ${CMAKE_SOURCE_DIR}/src/utils.hpp
)

IF (APPLE)
  target_link_libraries(
    Framework
    SOIL
    "-framework OpenGL"
    "-framework Cocoa"
    "-framework IOKit"
    "-framework CoreVideo"
    "-framework GLUT"
  )

  target_include_directories(
    Framework
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/
  )
ELSE()
  target_link_libraries(
    Framework
    freeglut
    SOIL
  )

  target_include_directories(
    Framework
    PUBLIC 
    ${FREEGLUT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/src/
  )
ENDIF()

