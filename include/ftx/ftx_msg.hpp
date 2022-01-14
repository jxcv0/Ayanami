#ifndef WS_MSG_HPP
#define WS_MSG_HPP

#include "msg_base.hpp"

#include <string_view>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Connection managment for FTX exchange
     * 
     */
    namespace ftx {
        /**
         * @brief base class for all ftx ws messages
         * https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
         * @tparam T 
         */
        template<typename T>
        class ftx_msg_base {

            /**
             * @brief Message type field determines what other fields are in the message body
             * 
             */
            enum class msg_type {
                ERROR,
                SUBSCRIBED,
                UNSUBSCRIBED,
                INFO,
                PARTIAL,
                UPDATE
            }
            
        private:
            std::string_view channel;
            std::string_view market;
            msg_type type;
        };

        /**
         * @brief Trade message from ftx websocket subscription
         * 
         */
        class ftx_trade_message : trade_msg_base<ftx_trade_message> {
            long time;      // unix time of trade (accuracy is exchange dependant)
            float price;    // the price the trade was executed at
            float qty;      // the total transacted volume
        public:

            // TODO - a method that parses json
            
            float price() {
                return price;
            }

            float qty() {
                return qty;
            }

            long time() {
                return time;
            }
        };
    } // namespace ftx
} // namespace ayanami

#endif