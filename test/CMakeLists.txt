cmake_minimum_required(VERSION 3.0.0)

enable_testing()

set(
    SOURCES
        TradeTests.cpp
)

add_executable(Tests ${SOURCES})

target_link_libraries(Tests PUBLIC
    gtest_main
)

target_include_directories(
    Tests
        PRIVATE
            ${PROJECT_SOURCE_DIR}/include
            ${PROJECT_SOURCE_DIR}/src

)

add_test(
    NAME Tests
    COMMAND Tests
)