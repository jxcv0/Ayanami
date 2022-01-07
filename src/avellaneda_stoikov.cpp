#include "avellaneda_stoikov.hpp"
#include <math.h>

void ayanami::av::res_price(const av_in& in, av_out& out) {
    out.res = (in.mid - (in.inv * in.risk * in.vol * in.time));
}

void ayanami::av::spread(const av_in& in, av_out& out) {
    out.spread = ((in.risk * in.vol * in.time) + ((2 / in.risk) * log(1 + (in.risk / in.liq)))) / 2;
}