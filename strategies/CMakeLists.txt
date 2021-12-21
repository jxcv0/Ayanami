cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_CXX_STANDARD 11)

add_executable(avellaneda_stoikov AvellanedaStoikov.cpp)

target_link_libraries(
    avellaneda_stoikov 
        PUBLIC
            ayanami
)