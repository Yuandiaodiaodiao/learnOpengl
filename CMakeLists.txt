cmake_minimum_required(VERSION 3.15)
project(learnOpengl)

set(CMAKE_CXX_STANDARD 14)
include_directories("./include")
include_directories("packages/glfw.3.3.0.1/include")

link_directories("packages/glfw.3.3.0.1/lib-vc2019")
SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:"msvcrt.lib")

add_executable(learnOpengl main.cpp glad.c) 
target_link_libraries(learnOpengl
        glfw3
        )