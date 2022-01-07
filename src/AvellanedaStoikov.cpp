#include "AvellanedaStoikov.hpp"
#include <math.h>

ayanami::av::Order::Order(double t) : tick(t){};

void ayanami::av::res_price(const AV_in& in, AV_out& out) {
    out.res = (in.mid - (in.inv * in.risk * in.vol * in.time));
}

void ayanami::av::spread(const AV_in& in, AV_out& out) {
    out.spread = ((in.risk * in.vol * in.time) + ((2 / in.risk) * log(1 + (in.risk / in.liq)))) / 2;
}