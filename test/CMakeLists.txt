cmake_minimum_required(VERSION 3.0.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

set(
    SOURCES
        LimitOrderBookTests.cpp
        TradeSeriesTests.cpp
)

add_executable(AyanamiTests ${SOURCES})

target_link_libraries(
    AyanamiTests 
        PUBLIC
            Ayanami
            gtest_main
)

add_test(
    NAME AyanamiTests
    COMMAND AyanamiTests
)