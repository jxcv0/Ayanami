#ifndef TRADE_HPP
#define TRADE_HPP

#include <iostream>

using namespace std;

// Represents a trade event
class Trade {

    private:

        // The time (Unix time)
        int time;

        // The trade price
        double price;

        // The signed trade volume
        int qty;

        // The symbol of the traded asset
        // TODO could be enum
        string symbol;
        
    public:

        // The constructor
        Trade(int t, double p, int q, string s, string sym);

        // Get the time
        int time;

        // Get the trade price
        double price;

        // Get the trade volume
        int qty;

        // get the symbol of the traded asset
        string symbol;
};

#endif