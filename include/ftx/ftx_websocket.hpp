#ifndef FTX_WEBSOCKET_HPP
#define FTX_WEBSOCKET_HPP

#include "json.hpp"
#include <cpprest/json.h>

#include <map>
#include <variant>
#include <vector>

namespace Ayanami {

    /**
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace FTX {

        /**
         * @brief Webocket response channel
         * 
         */
        enum class Channel {
            NONE,
            TRADES,
            ORDERBOOK,
            ORDERS
        };

        /**
         * @brief Websocket response type
         * 
         */
        enum class Type {
            NONE,
            ERROR,
            SUBSCRIBED,
            UNSUBSCRIBED,
            INFO,
            PARTIAL,
            UPDATE,
            PONG
        };

        /**
         * @brief Generic websocket response message from the FTX websocket.
         * Members of this struct will be assigned or cleared depending on the message.
         * 
         */
        struct FTX_WebsocketMessage {
            Type type;
            Channel channel;
            std::string_view market; // only ever will be one market for mm strategy
            int code;
            std::string_view msg;
            std::map<double, double> orderbookData; // only used for orderbook messages
            std::map<double, std::pair<double, int>> ordersData; // only used for orders messages
            
            /**
             * @brief Reset all fields in this message
             * 
             */
            void reset();
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
            Ayanami::LookupMap<std::string_view, Channel, channelValues.size()>{{channelValues}};

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
            Ayanami::LookupMap<std::string_view, Type, typeValues.size()>{{typeValues}};

        /**
         * @brief Parse websocket response json string and update data in message struct.
         * This function is specific to the strategy and is not a generic parsing function.
         * 
         * @param update the struct to update
         * @param str the json string from the websocket
         */
        void parse_ws_response(FTX_WebsocketMessage &update, const std::string& str);
    } // namespace ftx
} // namespace ayanami

#endif