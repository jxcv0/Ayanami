cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

set(
    SOURCES
        limit_order_book_tests.cpp
        encryption_tests.cpp
        avellaneda_stoikov_tests.cpp
        json_tests.cpp
        ftx/ftx_api_tests.cpp
)

add_executable(all_tests ${SOURCES})

target_link_libraries(
    all_tests 
        PUBLIC
            ayanami
            gtest_main
)

add_test(
    NAME all_tests
    COMMAND all_tests
)