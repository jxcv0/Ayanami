#include "Trade.hpp"

using namespace std;

Trade::Trade(int t, double p, int q, string sym) {
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

int Trade::getQty() {
    return qty;
}

string Trade::getSymbol() {
    return symbol;
}