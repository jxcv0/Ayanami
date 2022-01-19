#include <gtest/gtest.h>

#include "limit_order_book.hpp"
#include "json.hpp"

TEST(LimitOrderBookTests, update_orderbook) {
    
    std::map<double, double> update = {
        {42730.0, 1.8567},
        {42732.0, 0.109},
        {42737.0, 1.2402},
        {42741.0, 10.6792},
        {42742.0, 0.561},
        {42747.0, 1.0843},
        {42776.0, 11.1424},
        {42779.0, 2.8618},
        {42825.0, 12.423}
    };

    
}