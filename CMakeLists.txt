cmake_minimum_required(VERSION 3.0.0)
project(Ayanami VERSION 0.1.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

set(
    SOURCES
        src/main.cpp
        src/Trade.cpp
)

set(
    HEADERS
        include/Trade.hpp
)

add_executable(Ayanami ${SOURCES} ${HEADERS})

target_include_directories(
    Ayanami
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include

)

add_subdirectory(googletest)
add_subdirectory(test)
