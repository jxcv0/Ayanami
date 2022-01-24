cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)

link_libraries(ayanami)

add_executable(ftxmm ftx_mm.cpp)
add_executable(bbmm bybit_mm.cpp)