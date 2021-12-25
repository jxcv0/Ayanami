cmake_minimum_required(VERSION 3.16.0)
project(Ayanami VERSION 0.1.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        1a3e2a265f35e604378156cd675b11ef0a184627
)
FetchContent_MakeAvailable(googletest)

find_package(cpprestsdk REQUIRED)
find_package(Boost 1.71.0 REQUIRED)

set(
  SOURCES
    src/Websocket.cpp
    src/TradeSeries.cpp
    src/TimeSeries.cpp
    src/PriceSeries.cpp
    src/ftx/FTX_OrderBookMsgs.cpp
    src/LimitOrderBook.cpp
)

set(
  HEADERS
    include/Websocket.hpp
    include/TradeSeries.hpp
    include/TimeSeries.hpp
    include/PriceSeries.hpp
    include/ftx/FTX_OrderBookMsgs.hpp
    include/LimitOrderBook.hpp
)

add_library(ayanami STATIC ${SOURCES} ${HEADERS})

target_include_directories(
  ayanami
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
      ${PROJECT_SOURCE_DIR}/build/_deps/cpprestsdk-src/Release/include/cpprest
      ${Boost_INCLUDE_DIRS}
)

target_link_libraries(
  ayanami
    PUBLIC
      cpprestsdk::cpprest
      ${Boost_LIBRARIES}
)

add_subdirectory(test)
add_subdirectory(strategies)