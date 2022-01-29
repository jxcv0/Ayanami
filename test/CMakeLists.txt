cmake_minimum_required(VERSION 3.22.1)
project(ayanamitestsuite)

enable_testing()

set(
    SOURCES
    messages_tests.cpp
    limit_order_book_tests.cpp
    encryption_tests.cpp
    avellaneda_stoikov_tests.cpp
    ftx/ftx_api_tests.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} 
    PUBLIC
    ayanami
    gtest_main
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)