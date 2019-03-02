project(screensaver.example.windows.gles)

cmake_minimum_required(VERSION 3.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR})

find_package(Kodi REQUIRED)

if(APP_RENDER_SYSTEM STREQUAL "gl")
  set(DEPLIBS ${OPENGL_LIBRARIES})
  set(INCLUDES ${OPENGL_INCLUDE_DIR})
  add_definitions(${OPENGL_DEFINITIONS})
else()
  find_package(OpenGLES REQUIRED)
  set(DEPLIBS ${OPENGLES_LIBRARIES})
  set(INCLUDES ${OPENGLES_INCLUDE_DIR})
  add_definitions(${OPENGLES_DEFINITIONS})
endif()

include_directories(${KODI_INCLUDE_DIR}/..)

set(EXAMPLE_SOURCES src/example.cpp)

build_addon(screensaver.example.windows.gles EXAMPLE DEPLIBS)
include(CPack)
