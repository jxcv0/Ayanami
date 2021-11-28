#include "LimitOrderBook.hpp"
#include <numeric>

Ayanami::LimitOrderBook::LimitOrderBook() {
    populated = false;
}

void Ayanami::LimitOrderBook::insert(const double &price, const double &size) {
    if (size != 0) {
        values[price] = size;
    } else {
        remove(price);
    }
}

void Ayanami::LimitOrderBook::remove(const double &price) {
    values.erase(price);
}   

double Ayanami::LimitOrderBook::atPrice(const double &price) {
    return values.at(price);
}

double Ayanami::LimitOrderBook::depth() {
    return std::accumulate(std::begin(values), std::end(values), 0,
        [](const double previous, const auto &value){return previous + value.second});
}

double Ayanami::LimitOrderBook::depth(const double &range) {
    
}