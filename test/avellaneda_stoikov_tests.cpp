#include <gtest/gtest.h>

#include "avellaneda_stoikov.hpp"

TEST(avellaneda_stoikov_tests, init_bids_test) {
    ayanami::av::av_out out(1);
    out.res = 1011.5;
    out.spread = 3;
    std::vector<ayanami::av::order> bids;
}

TEST(avellaneda_stoikov_tests, modify_bids_test) {

}

TEST(avellaneda_stoikov_tests, init_asks_test) {

}

TEST(avellaneda_stoikov_tests, modify_asks_test) {

}