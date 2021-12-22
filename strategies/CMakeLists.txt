cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

link_libraries(ayanami)

add_executable(avellaneda_stoikov AvellanedaStoikov.cpp)
add_executable(classic Classic.cpp)