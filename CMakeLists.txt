cmake_minimum_required(VERSION 3.15)
#set(CMAKE_C_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.23.28105/bin/Hostx86/x86/cl.exe")
#set(CMAKE_CXX_COMPILER "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.23.28105/bin/Hostx86/x86/cl.exe")
project(learnOpengl)

set(CMAKE_CXX_STANDARD 14)

include_directories("./include")
include_directories("packages/glfw.3.3.0.1/include")
include_directories("packages/Assimp/include")

link_directories("packages/glfw.3.3.0.1/lib-vc2019")
link_directories("packages/Assimp/lib")
SET(CMAKE_EXE_LINKER_FLAGS /NODEFAULTLIB:"msvcrt.lib")

add_executable(learnOpengl main.cpp include/bone.cpp include/ccd.cpp include/ccd.h  include/bone.h glad.c include/SharderM.h include/stb_image.h stb_image.cpp include/CameraM.h include/mesh.h include/model.h )
target_link_libraries(learnOpengl
        glfw3
        assimpd        )