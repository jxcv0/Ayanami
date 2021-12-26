#include "PriceSeries.hpp"

#include <numeric>
#include <algorithm>
#include <math.h>
#include <iostream>

ayanami::PriceSeries::PriceSeries(int max) : max_size_(max) {}

void ayanami::PriceSeries::trim() {
    if (series_.size() > max_size_) {
        series_.erase(series_.begin());
    }
}

void ayanami::PriceSeries::add_price(double price) {
    series_.push_back(price);
    trim();
}

int ayanami::PriceSeries::size() {
    return series_.size();
}

double ayanami::PriceSeries::mean() {
    double sum = std::accumulate(series_.begin(), series_.end(), 0);
    return sum / series_.size();
}

double ayanami::PriceSeries::variance() {
    std::vector<double> diff(series_.size());
    double mean = this->mean();
    std::transform(series_.begin(), series_.end(), diff.begin(), 
        [mean](double x) {return x - mean; });
    return std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0) / series_.size();
}

double ayanami::PriceSeries::std_dev() {
    return std::sqrt(this->variance());
}