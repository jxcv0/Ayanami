#include "LimitOrderBook.hpp"
#include <numeric>
#include <algorithm>
#include <vector>

Ayanami::LimitOrderBook::LimitOrderBook() {
    populated = false;
}

Ayanami::LimitOrderBook::LimitOrderBook(std::map<double, double>& map) {
    values.insert(map.begin(), map.end());
    populated = true;
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
        [](double i, const std::map<double, double>::value_type& j)
            {return i + std::abs(j.second);}
    );
}

double Ayanami::LimitOrderBook::depth(const double &range) {
    std::map<double, double> result;

    // This works, but needs to be faster. Why doesnt std::copy_if() work???
    for (std::map<double, double>::value_type& i : getAsks()) {
        if (i.first <= (bestAsk() + range)) {
            result.insert(i);
        }
    }

    // See above
    for (std::map<double, double>::value_type& i : getBids()) {
        if (i.first >= (bestBid() - range)) {
            result.insert(i);
        }
    }

    return std::accumulate(
        std::begin(result), std::end(result), 0,
        [](double d, const std::map<double, double>::value_type& i)
            {return d + std::abs(i.second);}
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

double Ayanami::LimitOrderBook::delta() {
    return std::accumulate(values.begin(), values.end(), 0,
        [](double d, const std::map<double, double>::value_type& i)
            {return d + i.second;}
    );
}

double Ayanami::LimitOrderBook::delta(const double& range) {
    std::map<double, double> result;

    // This works, but needs to be faster. Why doesnt std::copy_if() work???
    for (std::map<double, double>::value_type& i : getAsks()) {
        if (i.first <= (bestAsk() + range)) {
            result.insert(i);
        }
    }

    // See above
    for (std::map<double, double>::value_type& i : getBids()) {
        if (i.first >= (bestBid() - range)) {
            result.insert(i);
        }
    }

    return std::accumulate(
        std::begin(result), std::end(result), 0,
        [](double d, const std::map<double, double>::value_type& i)
            {return d + i.second;}
    );
}