cmake_minimum_required(VERSION 3.22.1)
project(Ayanami VERSION 0.1.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")

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
find_package(OpenSSL REQUIRED)

set(
  SOURCES
    src/https.cpp
    src/trade_series.cpp
    src/price_series.cpp
    src/limit_order_book.cpp
    src/encryption.cpp
    src/avellaneda_stoikov.cpp
    src/ftx/ftx_ws.cpp
    src/ftx/ftx_rest.cpp
)

set(
  HEADERS
    include/api_keys.hpp
    include/https.hpp
    include/trade_series.hpp
    include/price_series.hpp
    include/limit_order_book.hpp
    include/encryption.hpp
    include/avellaneda_stoikov.hpp
    include/order_machine.hpp
    include/msg_base.hpp
    include/ftx/ftx_ws.hpp
    include/ftx/ftx_rest.hpp
    include/ftx/ftx_msg.hpp
)

add_library(ayanami STATIC ${SOURCES} ${HEADERS})

target_include_directories(
  ayanami
    PUBLIC
      ${PROJECT_SOURCE_DIR}/include
      ${cpprestsdk_INCLUDE_DIRS}
      ${Boost_INCLUDE_DIRS}
)

target_link_libraries(
  ayanami
    PUBLIC
      cpprestsdk::cpprest
      ssl
      crypto
      ${Boost_LIBRARIES}
)

add_subdirectory(test)
add_subdirectory(strategy)