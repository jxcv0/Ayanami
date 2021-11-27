#include "LimitOrderBook.hpp"

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

}

double Ayanami::LimitOrderBook::depth(const double &range) {
    
}