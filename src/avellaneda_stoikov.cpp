#include "avellaneda_stoikov.hpp"
#include <math.h>

ayanami::av::av_in::av_in(double r, double l, double i) : liq(l), risk(r), inv(i) {};

void ayanami::av::res_price(const av_in& in, av_out& out) {
    out.res = (in.mid - (in.inv * in.risk * in.vol * in.time));
}

void ayanami::av::spread(const av_in& in, av_out& out) {
    out.spread = ((in.risk * in.vol * in.time) + ((2 / in.risk) * log(1 + (in.risk / in.liq)))) / 2;
}

// TODO - orders should now be std::map<double, std::pair<double, int>>
void ayanami::av::generate_bids(const av_out& out, std::map<double, int>& bids, double interval, int buffer) {
    // bids are initialized from highest price to lowest
    double optimal = out.res - (out.spread / 2);
    for (size_t i = 0; i < buffer ; i++) {
        bids[optimal] = 1; // will be overwritten with id by ws message parser
        optimal -= interval;
    }
}

// TODO - orders should now be std::map<double, std::pair<double, int>>
void ayanami::av::generate_asks(const av_out& out, std::map<double, int>& asks, double interval, int buffer) {
    // bids are initialized from lowest price to highest
    double optimal = out.res + (out.spread / 2);
    for (size_t i = 0; i < buffer ; i++) {
        asks[optimal] = 1; // will be overwritten by ws message parser
        optimal += interval;
    }
}