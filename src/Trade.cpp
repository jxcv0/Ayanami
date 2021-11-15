#include "Trade.hpp"

Trade::Trade(int t, double p, int q, string s, string sym) {
    time = t;
    price = p;
    qty = q;
    side = s;
    symbol = sym;
}

int Trade::time() {
    return time;
}

double Trade::price() {
    return price
}

int Trade::qty() {
    return qty;
}

string Trade::symbol() {
    return symbol;
}