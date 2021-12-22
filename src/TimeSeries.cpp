#include "TimeSeries.hpp"

ayanami::timeseries::Candle::Candle(double o, double h, double l, double c,double v)
    : open(o)
    , high(h)
    , low(l)
    , close(c)
    , vol(v){}

ayanami::timeseries::TimeSeries::TimeSeries(int maxSize) : maxSize_(maxSize){}

void ayanami::timeseries::TimeSeries::trim() {
    if (series_.size() > maxSize_) {
        series_.erase(series_.begin());
    }
}

void ayanami::timeseries::TimeSeries::add_candle(long t, double o, double h, double l, double c,double v) {
    series_.insert(std::make_pair(t, Candle(o, h, l, c, v)));
    trim();
}

int ayanami::timeseries::TimeSeries::size() {
    return series_.size();
}