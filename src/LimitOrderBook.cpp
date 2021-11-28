#include "LimitOrderBook.hpp"
#include <numeric>
#include <algorithm>
#include <vector>

Ayanami::LimitOrderBook::LimitOrderBook() {
    populated = false;
}

void Ayanami::LimitOrderBook::insert(const double& price, const double& size) {
    if (size != 0) {
        values[price] = size;
    } else {
        remove(price);
    }
}

void Ayanami::LimitOrderBook::remove(const double& price) {
    values.erase(price);
}   

double Ayanami::LimitOrderBook::atPrice(const double& price) {
    return values.at(price);
}

void Ayanami::LimitOrderBook::setPopulated(bool flag) {
    populated = flag;
}
double Ayanami::LimitOrderBook::bestAsk() {
    return getAsks().begin()->first;
}

double Ayanami::LimitOrderBook::bestBid() {
    return getBids().crbegin()->first;
}

double Ayanami::LimitOrderBook::depth() {
    return std::accumulate(
        std::begin(values), std::end(values), 0,
        [](double value, const std::map<double, double>::value_type& n)
            {return value + std::abs(n.second);}
    );
}

double Ayanami::LimitOrderBook::depth(const double &range) {
    std::map<double, double> result;

    // // Copy asks in range -- getAsks().find(bestAsk() * (1 + range)
    std::copy(getAsks().begin(), getAsks().end(), std::inserter(result, std::begin(result)));

    // // Copy bids in range
    // std::copy(getBids().begin() , getBids().find(bestBid() * (1 - range)),
    //     std::inserter(result, result.end()));
    
    // Return depth
    return std::accumulate(
        std::begin(result), std::end(result), 0,
        [](double value, const std::map<double, double>::value_type& n)
            {return value + std::abs(n.second);}
    );
}

std::map<double, double> Ayanami::LimitOrderBook::getAsks() {
    std::map<double, double> asks;
    std::copy_if(values.begin(), values.end(), std::inserter(asks, std::begin(asks)),
        [](const std::map<double, double>::value_type& n){return (n.second < 0);}
    );
    return asks;
}

std::map<double, double> Ayanami::LimitOrderBook::getBids() {
    std::map<double, double> bids;
    std::copy_if(values.begin(), values.end(), std::inserter(bids, std::begin(bids)),
        [](const std::map<double, double>::value_type& n){return (n.second > 0);}
    );
    return bids;
}