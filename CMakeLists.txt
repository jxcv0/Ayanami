cmake_minimum_required(VERSION 3.18.0)
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
FetchContent_MakeAvailable(googletest)

set(
  SOURCES
    src/Trade.cpp
    src/Websocket.cpp
    src/Socket.cpp
)

set(
  HEADERS
    include/Trade.hpp
    include/Websocket.hpp
    include/Socket.hpp
)

add_library(Ayanami STATIC ${SOURCES} ${HEADERS})

target_include_directories(
  Ayanami
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
)

add_subdirectory(test)