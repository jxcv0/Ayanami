#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include <vector>
#include <functional>
#include <variant>
#include <any>
#include <iostream>

namespace Ayanami {

    /**
     * @brief Overload pattern for message bus visitor
     * 
     * @tparam Types types
     */
    template<typename... Types>
    struct Visitor : Types... {
        using Types::operator()...;
    };

    /**
     * @brief Concept for ensuring T is one of Ts... and therefor useable by the bus
     * 
     * @tparam T the individual param
     * @tparam Ts the parameter pack
     */
    template<typename T, typename... Ts>
    concept valid = std::disjunction_v<std::is_same<T, Ts>...>;

    /**
     * @brief Message bus distributes a message to handlers via a visitor
     * 
     * @tparam Messages the message types known at compile time
     */
    template<typename... Messages>
    class MessageBus {
        std::vector<std::variant<Messages...>> queue_;

    public:

        /**
         * @brief Distribute all messages in the queue to the visitors
         * 
         * @param visitor the visitors
         */
        void operator()(auto visitor) {
            while (!queue_.empty()) {
                std::visit(visitor, queue_.front());
                queue_.erase(queue_.begin());
            }
        }

        /**
         * @brief Distribute message and all other messages in the queue to visitors
         * 
         * @tparam Message the message type which must be the message must be one of the templated
         * message bus types
         * @param visitor the bus visitor
         * @param message the message
         */
        template<valid<Messages...> Message>
        void operator()(auto visitor, Message message){
            push_back(message);
            while (!queue_.empty()) {
                std::visit(visitor, queue_.front());
                queue_.erase(queue_.begin());
            }
        }

        /**
         * @brief Push a message to the back of the message queue
         * 
         * @tparam Message the message must be one of the templated message bus types
         * @param message the message
         */
        template<valid<Messages...> Message>
        void push_back(Message message) {
            queue_.push_back(message);
        }

        /**
         * @brief Get the size of the message queue
         * 
         * @return size_t the queue size
         */
        size_t size(){
            return queue_.size();
        }
    };

    enum class MessageType {
        INFO,
        SUBSCRIBED,
        UNSUBSCRIBED,
        INFO,
        PARTIAL,
        UPDATE
    };

    // These messages are quite generic and can be reused for other excanges after renaming.

    /**
     * @brief Base message type for the FTX exchange websocket messages.
     * All messages have a Type;
     */
    struct FtxMessage {
        MessageType type;
    };

    /**
     * @brief Info messages can carry a code and message.
     * On code 20001, reconnection to the exchange should be attempted
     * 
     */
    struct InfoMessage : FtxMessage {
        int code;
        std::string_view msg;
    };

    /**
     * @brief FTX Orderbook update message with bid and ask data
     * 
     */
    struct OrderbookMessage : FtxMessage {
        std::string_view channel;
        std::string_view market;
        double time;
        int checksum;
        std::map<double, double> bids;
        std::map<double, double> asks;
    };
} // namespace Ayanami

#endif