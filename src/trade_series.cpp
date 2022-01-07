#include "trade_series.hpp"

ayanami::series::series(int maxSize) {
    maxSize_ = maxSize;
};

void ayanami::series::trim() {
    if (series_.size() > maxSize_) {
        series_.erase(series_.begin());
    }
}

int ayanami::series::size() {
    return series_.size();
}

void ayanami::series::add_trade(long time, double price, double qty) {
    series_.insert(std::make_pair(time, std::make_pair(price, qty)));
    trim();
};