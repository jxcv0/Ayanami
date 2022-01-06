#include "AvellanedaStoikov.hpp"
#include <math.h>

double ayanami::av::res_price(double mid, int inv, double risk, double vol, double time) {
    return mid - (inv * risk * vol * time);
}

double ayanami::av::spread(double risk, double vol, double time, double k) {
    return ((risk * vol * time) + ((2 / risk) * log(1 + (risk / k)))) / 2;
}