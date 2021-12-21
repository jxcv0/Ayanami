#include "TradeSeries.hpp"

ayanami::tradeseries::Trade::Trade(const double& price, const double& qty) : price(price), qty(qty) {};

ayanami::tradeseries::Series::Series(const int& maxSize) {
    maxSize_ = maxSize;
};

int ayanami::tradeseries::Series::size() {
    return s.size();
}

void ayanami::tradeseries::Series::add_trade(const long& time, const double& price, const double& qty) {
    s.insert(std::make_pair(time, Trade(price, qty)));
    trim();
};

void ayanami::tradeseries::Series::trim() {
    if (s.size() > maxSize_) {
        s.erase(s.begin());
    }
}