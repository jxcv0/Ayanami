cmake_minimum_required(VERSION 3.0.0)
project(Ayanami VERSION 0.1.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        1a3e2a265f35e604378156cd675b11ef0a184627
)

FetchContent_Declare(
  websocketpp
  GIT_REPOSITORY https://github.com/zaphoyd/websocketpp.git
  GIT_TAG        1b11fd301531e6df35a6107c1e8665b1e77a2d8e
)

FetchContent_MakeAvailable(googletest websocketpp)

set(
    SOURCES
        src/Trade.cpp
)

set(
    HEADERS
        include/Trade.hpp
)

add_library(Ayanami ${SOURCES} ${HEADERS})

target_include_directories(
    Ayanami
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include

)

add_subdirectory(test)