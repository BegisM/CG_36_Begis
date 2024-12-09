cmake_minimum_required(VERSION 3.15)
project(OpenGL_Project)

set(CMAKE_CXX_STANDARD 17)

# Find OpenGL and GLUT
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(OpenGL_Project test2.cpp)

# Link OpenGL and GLUT libraries
target_link_libraries(OpenGL_Project PRIVATE OpenGL::GL GLUT::GLUT)
