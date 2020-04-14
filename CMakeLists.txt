cmake_minimum_required(VERSION 3.3)
project(openGL_tutorial)
if (CMAKE_SYSTEM MATCHES "Linux")
    add_definitions(-D__Linux__)
endif()
find_package(OpenGL REQUIRED)
if(NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif(NOT OPENGL_FOUND)
set(GL_LIBRARY GL GLU X11)

add_executable(openGL_tutorial main.cpp)
target_link_libraries(openGL_tutorial glfw GLEW libGLEW.so libGLU.so libGL.so)

