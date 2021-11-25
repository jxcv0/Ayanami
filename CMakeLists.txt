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

find_package(cpprestsdk REQUIRED)

set(
  SOURCES
    src/Trade.cpp
    src/BybitWebsocket.cpp
    src/BybitWSHandler.cpp
)

set(
  HEADERS
    include/Trade.hpp
    include/Websocket.hpp
    include/APIKeys.hpp
    include/BybitWSHandler.hpp
)

add_library(Ayanami STATIC ${SOURCES} ${HEADERS})

target_include_directories(
  Ayanami
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
      ${PROJECT_SOURCE_DIR}/build/_deps/cpprestsdk-src/Release/include/cpprest
)

target_link_libraries(
  Ayanami
    PUBLIC
      cpprestsdk::cpprest
)

add_subdirectory(test)