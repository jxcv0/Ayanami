#include "TradeSeries.hpp"

ayanami::tradeseries::Trade::Trade(double price, double qty) : price(price), qty(qty) {};

ayanami::tradeseries::Series::Series(int maxSize) {
    maxSize_ = maxSize;
};

void ayanami::tradeseries::Series::trim() {
    if (s.size() > maxSize_) {
        s.erase(s.begin());
    }
}

int ayanami::tradeseries::Series::size() {
    return s.size();
}

void ayanami::tradeseries::Series::add_trade(long time, double price, double qty) {
    s.insert(std::make_pair(time, Trade(price, qty)));
    trim();
};