#ifndef FTX_WEBSOCKET_HPP
#define FTX_WEBSOCKET_HPP

#include <cpprest/json.h>

#include <map>
#include <variant>
#include <vector>

namespace Ayanami {

    /**
     * @brief Constexpr map for faster lookups
     * 
     * @tparam Key map key type
     * @tparam Value map value type
     * @tparam Size size of map must be known at compiletime
     */
    template<typename Key, typename Value, std::size_t Size>
    struct LookupMap {
        std::array<std::pair<Key, Value>, Size> data;

        [[nodiscard]] constexpr Value at(const Key &key) const {

            // linear search function is apparently faster for small maps than binary search
            const auto itr = std::find_if(data.begin(), data.end(), [&key](const auto &v) {
                return v.first == key;
            });

            if (itr != data.end()) {
                return itr->second;
            } else {
                throw std::range_error("Not Found");
            }
        }
    };

    /**
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace FTX {

        /**
         * @brief Orderbook channel enums
         * 
         */
        enum class Channel {
            TRADES,
            ORDERBOOK,
            ORDERS
        };

        /**
         * @brief Orderbook channel enums
         * 
         */
        enum class Market {
            BTCPERP
        };

        enum class Type {
            ERROR,
            SUBSCRIBED,
            UNSUBSCRIBED,
            INFO,
            PARTIAL,
            UPDATE,
            PONG
        };

        /**
         * @brief Order/trade side enums
         * 
         */
        enum class Side {
            BUY,
            SELL
        };

        /**
         * @brief Channel enum lookup values and LookupMap
         * 
         */
        static constexpr std::array<std::pair<std::string_view, Channel>, 3> channelValues {{
            {"trades", Channel::TRADES},
            {"orderbook", Channel::ORDERBOOK},
            {"orders", Channel::ORDERS}
        }};
        static constexpr auto channelMap =
            LookupMap<std::string_view, Channel, channelValues.size()>{{channelValues}};

        /**
         * @brief Channel enum lookup values and LookupMap
         * 
         */
        static constexpr std::array<std::pair<std::string_view, Market>, 1> marketValues {{
            {"BTC-PERP", Market::BTCPERP}     // this is here as others will be added later
        }};
        static constexpr auto marketMap =
            LookupMap<std::string_view, Market, marketValues.size()>{{marketValues}};

        /**
         * @brief Type enum lookup values and LookupMap
         * 
         */
        static constexpr std::array<std::pair<std::string_view, Type>, 7> typeValues = {{
            {"error", Type::ERROR},
            {"subscribed", Type::SUBSCRIBED},
            {"unsubscribed", Type::UNSUBSCRIBED},
            {"info", Type::INFO},
            {"partial", Type::PARTIAL},
            {"update", Type::UPDATE},
            {"pong", Type::PONG}
        }};
        static constexpr auto typeMap =
            LookupMap<std::string_view, Type, typeValues.size()>{{typeValues}};

        /**
         * @brief Side enum lookup values and LookupMap
         * 
         */
        static constexpr std::array<std::pair<std::string_view, Side>, 2> sideValues = {{
            {"buy", Side::BUY},
            {"sell", Side::SELL}
        }};
        static constexpr auto sideMap =
            LookupMap<std::string_view, Side, sideValues.size()>{{sideValues}};

        /**
         * @brief Datatype that represents the data field of trades type message
         * 
         */
        struct Trades {
            int id;
            double price;       // is double as cppresdk does not convert to float
            double size;        // is double as cppresdk does not convert to float
            Side side;
            bool liquidation;
            std::string time;
        };

        /**
         * @brief Datatype that represents the data field of orderbook type message
         * 
         */
        struct Orderbook {
            // TODO
        };

        /**
         * @brief Datatype that represents the data field of order type message
         * 
         */
        struct Orders {
            // TODO
        };

        /**
         * @brief FTX websocket message datatype
         * 
         */
        struct FTXWebsocketMsg {
            Type type;
            Channel channel;
            Market market;
            int code;
            std::string_view msg;
            // a single trades message may contain multiple trades
            std::variant<std::vector<Trades>, Orderbook, Orders> data;
        };


        /**
         * @brief Parse a JSON message into an ftx_ws_msg
         * 
         * TODO - find and measure speed of std::any alternatives
         * 
         * @param str the JSON string to parse
         * @return the parsed ftx message as an ftx_ws_msg with ambiguous type
         */
        FTXWebsocketMsg parse(const std::string& str);

        /**
         * @brief TODO
         * 
         * @param msg 
         * @return std::variant<Trades, Orderbook, Orders> 
         */
        std::variant<Trades, Orderbook, Orders> exctract_data(const FTXWebsocketMsg &msg);

        /**
         * @brief Populate an orderbook with a "partial" JSON message
         * 
         * @param orderbook the orderbook to populate
         * @param data the "data" field of the JSON message
         */
        void populate_orderbook(std::map<double, double>& orderbook, web::json::value& data);

        /**
         * @brief Update and orderbook with an "update" JSON message
         * 
         * @param orderbook the orderbook to update
         * @param data the "data" field of the JSON message
         */
        void update_orderbook(std::map<double, double>& orderbook, web::json::value& data);
    } // namespace ftx
} // namespace ayanami

#endif