#include "avellaneda_stoikov.hpp"
#include <math.h>

Ayanami::AV::AvIn::AvIn(double r, double l, double i, double v)
    : liq(l)
    , risk(r)
    , inv(i)
    , vol(v) {};

void Ayanami::AV::res_price(const AvIn& in, AvOut& out) {
    out.res = (in.mid - (in.inv * in.risk * in.vol * in.time));
}

void Ayanami::AV::spread(const AvIn& in, AvOut& out) {
    out.spread = ((in.risk * in.vol * in.time) + ((2 / in.risk) * log(1 + (in.risk / in.liq)))) / 2;
}