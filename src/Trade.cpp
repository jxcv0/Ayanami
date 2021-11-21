#include "Trade.hpp"

using namespace std;

Ayanami::Trade::Trade(int t, double p, double q, string sym) {
    time = t;
    price = p;
    qty = q;
    symbol = sym;
}

int Ayanami::Trade::getTime() {
    return time;
}

double Ayanami::Trade::getPrice() {
    return price;
}

double Ayanami::Trade::getQty() {
    return qty;
}

string Ayanami::Trade::getSymbol() {
    return symbol;
}