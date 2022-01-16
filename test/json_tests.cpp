#include <gtest/gtest.h>

#include "json.hpp"

TEST(JsonTests, json_file_to_string) {
    std::string expected("{\"channel\": \"trades\", \"market\": \"BTC-PERP\", \"type\": \"update\", \"data\": [{\"id\": 3084555351, \"price\": 43345.0, \"size\": 0.0023, \"side\": \"sell\", \"liquidation\": false, \"time\": \"2022-01-14T21:39:17.451561+00:00\"}]}");
    std::string actual = Ayanami::file_to_string("test/json_test_cases/ftx_trades.json");
    ASSERT_EQ(actual, expected);
}