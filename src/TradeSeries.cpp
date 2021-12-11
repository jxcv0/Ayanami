#include "TradeSeries.hpp"

Ayanami::TradeSeries::Trade::Trade(const double& price, const double& qty) : price(price), qty(qty) {};

Ayanami::TradeSeries::Series::Series(const int& maxSize) {
    _maxSize = maxSize;
};

int Ayanami::TradeSeries::Series::size() {
    return series.size();
}

void Ayanami::TradeSeries::Series::addTrade(const long& time, const double& price, const double& qty) {
    series.insert(std::make_pair(time, Trade(price, qty)));
    trim();
};

void Ayanami::TradeSeries::Series::trim() {
    if (series.size() > _maxSize) {
        series.erase(series.begin());
    }
}