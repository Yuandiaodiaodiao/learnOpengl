cmake_minimum_required(VERSION 3.15)
project(proj51)

set(CMAKE_CXX_STANDARD 14)

include_directories("./include")
add_executable(proj51 main.cpp ./include/Edge.cpp ./include/Face.cpp ./include/FException.cpp ./include/HalfEdge.cpp ./include/OBJFileReader.cpp ./include/Parser.cpp ./include/Point.cpp ./include/Solid.cpp ./include/SolidDelegate.cpp ./include/StringTokenizer.cpp ./include/TopologyException.cpp ./include/Trait.cpp ./include/Vertex.cpp)