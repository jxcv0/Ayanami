#include "avellaneda_stoikov.hpp"
#include <math.h>

ayanami::av::av_in::av_in(double r, double l, double i) : liq(l), risk(r), inv(i) {};

void ayanami::av::res_price(const av_in& in, av_out& out) {
    out.res = (in.mid - (in.inv * in.risk * in.vol * in.time));
}

void ayanami::av::spread(const av_in& in, av_out& out) {
    out.spread = ((in.risk * in.vol * in.time) + ((2 / in.risk) * log(1 + (in.risk / in.liq)))) / 2;
}

void ayanami::av::generate_bids(const av_out& out, std::map<double, order>& bids, double interval, int buffer) {
    // bids are initialized from highest price to lowest
    double optimal = out.res - (out.spread / 2);
    for (size_t i = 0; i < buffer ; i++) {
        order o;
        bids[optimal] = o;
        optimal -= interval;
    }    
}

void ayanami::av::generate_asks(const av_out& out, std::map<double, order>& asks, double interval, int buffer) {
    // bids are initialized from lowest price to highest
    double optimal = out.res + (out.spread / 2);
    for (size_t i = 0; i < buffer ; i++) {
        order o;
        asks[optimal] = o;
        optimal += interval;
    }    
}