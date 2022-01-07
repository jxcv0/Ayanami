#include "price_series.hpp"

#include <numeric>
#include <algorithm>
#include <math.h>
#include <iostream>

ayanami::price_series::price_series(int max) : max_size_(max) {}

void ayanami::price_series::trim() {
    if (series_.size() > max_size_) {
        series_.erase(series_.begin());
    }
}

void ayanami::price_series::add_price(double price) {
    series_.push_back(price);
    trim();
}

int ayanami::price_series::size() {
    return series_.size();
}

double ayanami::price_series::mean() {
    double sum = std::accumulate(series_.begin(), series_.end(), 0);
    return sum / series_.size();
}

double ayanami::price_series::variance() {
    std::vector<double> diff(series_.size());
    double mean = this->mean();
    std::transform(series_.begin(), series_.end(), diff.begin(), 
        [mean](double x) {return x - mean; });
    return std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0) / series_.size();
}

double ayanami::price_series::std_dev() {
    return std::sqrt(this->variance());
}