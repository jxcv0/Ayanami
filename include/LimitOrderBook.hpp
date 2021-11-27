#ifndef LIMITORDERBOOK_HPP
#define LIMITORDERBOOK_HPP

#include <map>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace Ayanami {

    /**
     * @brief Represents an exchange orderbook
     * 
     */
    class LimitOrderBook {
        private:
            std::map<double, double> values;
    };
}

#endif