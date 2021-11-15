cmake_minimum_required(VERSION 3.0.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

set(
    SOURCES
        TradeTests.cpp
        ${PROJECT_SOURCE_DIR}/src/Trade.cpp
)

add_executable(Tests ${SOURCES})

target_link_libraries(
    Tests 
        PUBLIC
            gtest_main
)

target_include_directories(
    Tests
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
)

add_test(
    NAME Tests
    COMMAND Tests
)