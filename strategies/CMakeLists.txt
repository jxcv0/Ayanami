cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(First First.cpp)

target_link_libraries(
    First 
        PUBLIC
            Ayanami
)