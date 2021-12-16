#include "LimitOrderBook.hpp"
#include <numeric>
#include <algorithm>
#include <vector>

Ayanami::LimitOrderBook::LimitOrderBook(const std::string& symbol) {
    _symbol = symbol;
    populated = false;
}

Ayanami::LimitOrderBook::LimitOrderBook(std::string symbol, std::map<double, double>& map) {
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

double Ayanami::LimitOrderBook::at_price(const double& price) {
    return values.at(price);
}

void Ayanami::LimitOrderBook::set_populated(bool flag) {
    populated = flag;
}

double Ayanami::LimitOrderBook::best_ask() {
    return get_asks().begin()->first;
}

double Ayanami::LimitOrderBook::best_bid() {
    return get_bids().crbegin()->first;
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
    for (std::map<double, double>::value_type& i : get_asks()) {
        if (i.first <= (best_ask() + range)) {
            result.insert(i);
        }
    }

    // See above
    for (std::map<double, double>::value_type& i : get_bids()) {
        if (i.first >= (best_bid() - range)) {
            result.insert(i);
        }
    }

    return std::accumulate(
        std::begin(result), std::end(result), 0,
        [](double d, const std::map<double, double>::value_type& i)
            {return d + std::abs(i.second);}
    );
}

std::map<double, double> Ayanami::LimitOrderBook::get_asks() {
    std::map<double, double> asks;
    std::copy_if(values.begin(), values.end(), std::inserter(asks, std::begin(asks)),
        [](const std::map<double, double>::value_type& n){return (n.second < 0);}
    );
    return asks;
}

std::map<double, double> Ayanami::LimitOrderBook::get_bids() {
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

    // This works, but needs to be faster. Why doesnt std::copy_if() work here
    for (std::map<double, double>::value_type& i : get_asks()) {
        if (i.first <= (best_ask() + range)) {
            result.insert(i);
        }
    }

    // See above
    for (std::map<double, double>::value_type& i : get_bids()) {
        if (i.first >= (best_bid() - range)) {
            result.insert(i);
        }
    }

    return std::accumulate(
        std::begin(result), std::end(result), 0,
        [](double d, const std::map<double, double>::value_type& i)
            {return d + i.second;}
    );
}

std::string Ayanami::LimitOrderBook::symbol() const {
    return _symbol;
};