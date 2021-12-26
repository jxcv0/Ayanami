#include <gtest/gtest.h>

#include "ftx/FTX_OrderBookMsgs.hpp"

#include <map>

TEST(FTX_OrderBookMsgsTests, populate_test) {

    std::map<double, double> orderbook;

    std::string msg = "{\"action\":\"partial\",\"asks\":[[50736,0.12690000000000001],[50737,0.095699999999999993],[50738,0.68589999999999995],[50739,1.4262999999999999],[50740,1.5772999999999999],[50741,0.098599999999999993],[50742,0.74150000000000005],[50743,0.59109999999999996],[50744,0.83840000000000003],[50745,1.9351],[50746,1.7717000000000001],[50747,1.2741],[50748,6.3735999999999997],[50749,3.8685],[50750,3.7088000000000001],[50751,1.0061],[50752,0.64319999999999999],[50753,0.061199999999999997],[50754,1.6566000000000001],[50755,0.60329999999999995],[50756,0.76339999999999997],[50757,4.2815000000000003],[50758,2.4020000000000001],[50759,1.4881],[50760,0.7319],[50761,0.76859999999999995],[50762,8.4039000000000001],[50763,0.42799999999999999],[50764,3.6274000000000002],[50765,0.092499999999999999],[50766,0.91649999999999998],[50767,19.388999999999999],[50768,0.96160000000000001],[50769,0.017000000000000001],[50770,0.68740000000000001],[50771,0.39889999999999998],[50772,0.79779999999999995],[50773,1.7484],[50774,1.8697999999999999],[50775,3.5070999999999999],[50776,0.094899999999999998],[50778,1.6020000000000001],[50779,0.79169999999999996],[50780,1.9956],[50781,0.085800000000000001],[50782,2.0062000000000002],[50783,0.49980000000000002],[50784,4.5785999999999998],[50785,0.68500000000000005],[50786,0.0097999999999999997],[50787,0.27360000000000001],[50788,0.95540000000000003],[50789,1.0422],[50790,1.0128999999999999],[50791,2.1073],[50792,0.22359999999999999],[50793,13.389799999999999],[50794,0.085400000000000004],[50795,0.3352],[50796,0.46629999999999999],[50797,0.22550000000000001],[50798,0.33310000000000001],[50799,0.059999999999999998],[50800,6.0038999999999998],[50801,2.0091000000000001],[50802,1.0573999999999999],[50803,0.001],[50804,5.2675000000000001],[50805,0.11],[50806,1.0991],[50807,4.3324999999999996],[50808,3.6892],[50809,0.85750000000000004],[50810,0.38819999999999999],[50811,0.059200000000000003],[50812,0.042999999999999997],[50813,2.0213999999999999],[50814,0.21260000000000001],[50817,0.121],[50818,0.25490000000000002],[50819,1.5901000000000001],[50820,8.6364000000000001],[50821,0.82099999999999995],[50822,0.001],[50823,5.5148999999999999],[50824,15.2804],[50825,16.592099999999999],[50826,2.855],[50827,0.0035000000000000001],[50828,1.0733999999999999],[50829,0.01],[50830,0.752],[50832,0.01],[50833,17.115600000000001],[50834,1.8369],[50835,0.4541],[50836,8.3290000000000006],[50837,0.41980000000000001],[50838,0.746],[50840,2.6364000000000001]],\"bids\":[[50735,6.0541999999999998],[50734,0.053699999999999998],[50733,0.55689999999999995],[50732,0.12529999999999999],[50731,1.8452999999999999],[50730,0.18149999999999999],[50729,1.3488],[50728,0.050000000000000003],[50727,0.1293],[50726,2.3418000000000001],[50725,0.95109999999999995],[50724,0.20630000000000001],[50723,0.64939999999999998],[50722,3.7746],[50721,2.4790000000000001],[50720,1.3396999999999999],[50719,0.82410000000000005],[50718,1.7621],[50717,4.6605999999999996],[50716,1.6048],[50715,0.88919999999999999],[50714,1.7885],[50713,0.34510000000000002],[50712,4.7422000000000004],[50711,3.4516],[50710,3.0038999999999998],[50709,0.40450000000000003],[50708,0.43390000000000001],[50707,0.0138],[50706,0.36509999999999998],[50705,5.7148000000000003],[50703,0.33529999999999999],[50702,0.84250000000000003],[50701,4.2896999999999998],[50700,4.6942000000000004],[50699,1.4764999999999999],[50698,0.29260000000000003],[50697,0.084400000000000003],[50696,0.0048999999999999998],[50694,0.13370000000000001],[50693,0.029999999999999999],[50692,9.9277999999999995],[50691,0.081100000000000005],[50690,0.59089999999999998],[50689,2.0762999999999998],[50688,0.11],[50687,1.6588000000000001],[50686,4.2857000000000003],[50685,0.79920000000000002],[50683,1.0915999999999999],[50682,1.02],[50681,22.879100000000001],[50680,4.5312999999999999],[50679,7.5101000000000004],[50678,0.62380000000000002],[50677,0.041200000000000001],[50676,0.48849999999999999],[50675,6.8956999999999997],[50674,6.8901000000000003],[50673,0.073599999999999999],[50672,1.1073],[50671,0.62749999999999995],[50670,0.30420000000000003],[50669,1.1097999999999999],[50668,0.10000000000000001],[50667,1.0281],[50664,0.051200000000000002],[50663,0.50239999999999996],[50661,1.3584000000000001],[50660,19.847999999999999],[50659,1.9040999999999999],[50658,0.20999999999999999],[50657,7.9151999999999996],[50656,0.1105],[50655,0.014800000000000001],[50654,0.055],[50653,0.82479999999999998],[50652,1.714],[50651,2.4241999999999999],[50650,1.4683999999999999],[50649,9.2209000000000003],[50648,0.48180000000000001],[50647,0.1971],[50646,0.77990000000000004],[50645,9.7466000000000008],[50644,0.3589],[50643,3.5137],[50642,1.5612999999999999],[50641,0.019699999999999999],[50640,0.0516],[50639,0.25750000000000001],[50638,1],[50637,0.92800000000000005],[50636,2.3448000000000002],[50635,0.995],[50634,0.111],[50633,0.83189999999999997],[50632,0.64590000000000003],[50631,1.2653000000000001],[50630,6.2237999999999998]],\"checksum\":1340093593,\"time\":1640428865.0542645}";
    web::json::value json = web::json::value::parse(msg);

    ayanami::ftx::populate_orderbook(orderbook, json);

    // asks
    ASSERT_DOUBLE_EQ(orderbook[50736], -0.12690000000000001);
    ASSERT_DOUBLE_EQ(orderbook[50737], -0.095699999999999993);
    ASSERT_DOUBLE_EQ(orderbook[50738], -0.68589999999999995);
    ASSERT_DOUBLE_EQ(orderbook[50739], -1.4262999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50740], -1.5772999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50741], -0.098599999999999993);
    ASSERT_DOUBLE_EQ(orderbook[50742], -0.74150000000000005);
    ASSERT_DOUBLE_EQ(orderbook[50743], -0.59109999999999996);

    // bids
    ASSERT_DOUBLE_EQ(orderbook[50735], 6.0541999999999998);
    ASSERT_DOUBLE_EQ(orderbook[50734], 0.053699999999999998);
    ASSERT_DOUBLE_EQ(orderbook[50733], 0.55689999999999995);
    ASSERT_DOUBLE_EQ(orderbook[50732], 0.12529999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50731], 1.8452999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50730], 0.18149999999999999);
    ASSERT_DOUBLE_EQ(orderbook[50729], 1.3488);
    ASSERT_DOUBLE_EQ(orderbook[50728], 0.050000000000000003);
}

TEST(FTX_OrderBookMsgsTests, update_test) {

    std::map<double, double> orderbook;
    orderbook[50673.0] = 10;
    orderbook[50694.0] = -10;
    orderbook[50696.0] = -10;
    orderbook[50711.0] = -10;
    orderbook[50786.0] = -10;

    std::string msg = "{\"time\": 1640433003.3059578, \"checksum\": 1720426769, \"bids\": [[50673.0, 17.8263]], \"asks\": [[50694.0, 0.35], [50696.0, 0.0], [50711.0, 3.2091], [50786.0, 0.8365]], \"action\": \"update\"}";
    web::json::value json = web::json::value::parse(msg);
    ayanami::ftx::update_orderbook(orderbook, json);

    // bids
    ASSERT_DOUBLE_EQ(orderbook[50673.0], 17.8263);
    
    // asks
    ASSERT_DOUBLE_EQ(orderbook.at(50694.0), -0.35);
    ASSERT_DOUBLE_EQ(orderbook.at(50711.0), -3.2091);
    ASSERT_DOUBLE_EQ(orderbook.at(50786.0), -0.8365);

    // rm 0
    ASSERT_ANY_THROW(orderbook.at(50696));
    ASSERT_EQ(orderbook.size(), 4);
}