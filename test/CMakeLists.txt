cmake_minimum_required(VERSION 3.0.0)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

enable_testing()

set(
    SOURCES
        TradeSeriesTests.cpp
        TimeSeriesTests.cpp
        PriceSeriesTests.cpp
        LimitOrderBookTests.cpp
        EncryptionTests.cpp
        ftx/FTX_HttpsTests.cpp
        ftx/FTX_OrderBookMsgsTests.cpp
        ftx/FTX_APIRequestsTests.cpp
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