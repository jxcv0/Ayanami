#include "TradeSeries.hpp"

ayanami::Series::Series(int maxSize) {
    maxSize_ = maxSize;
};

void ayanami::Series::trim() {
    if (series_.size() > maxSize_) {
        series_.erase(series_.begin());
    }
}

int ayanami::Series::size() {
    return series_.size();
}

void ayanami::Series::add_trade(long time, double price, double qty) {
    series_.insert(std::make_pair(time, std::make_pair(price, qty)));
    trim();
};