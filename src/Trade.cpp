#include "Trade.hpp"

Ayanami::Trade::Trade(const int& time, const double& price, const double& qty, const std::string& symbol) {
    _time = time;
    _price = price;
    _qty = qty;
    _symbol = symbol;
}

int Ayanami::Trade::getTime() {
    return _time;
}

double Ayanami::Trade::getPrice() {
    return _price;
}

double Ayanami::Trade::getQty() {
    return _qty;
}

std::string Ayanami::Trade::getSymbol() {
    return _symbol;
}