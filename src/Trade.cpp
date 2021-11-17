#include "Trade.hpp"

using namespace std;

Trade::Trade(int t, double p, double q, string sym) {
    time = t;
    price = p;
    qty = q;
    symbol = sym;
}

int Trade::getTime() {
    return time;
}

double Trade::getPrice() {
    return price;
}

double Trade::getQty() {
    return qty;
}

string Trade::getSymbol() {
    return symbol;
}