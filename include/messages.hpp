#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include <vector>
#include <functional>
#include <variant>
#include <string>
#include <stdexcept>
#include <map>

namespace Ayanami::Messages {

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

        [[nodiscard]] constexpr Value operator[](const Key &key) const {

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
     * @brief Read .json file and return the contents as a string
     * 
     * @param file the path to the file
     * @return the json as a string
     */
    std::string file_to_string(const char* file);

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

    /**
     * @brief Message type enumerators.
     * 
     */
    enum class MessageType {
        ERROR,
        SUBSCRIBED,
        UNSUBSCRIBED,
        INFO,
        PARTIAL,
        UPDATE,
        PONG
    };

    /**
     * @brief Message channel enumerators.
     * 
     */
    enum class Channel {
        ORDERBOOK,
        ORDERS,
        FILLS
    };
    
    /**
     * @brief Compile time evaluated map for assigning type enum to new message
     * 
     */
    static constexpr std::array<std::pair<std::string_view, MessageType>, 7> type_values {{
        {"error", MessageType::ERROR},
        {"subscribed", MessageType::SUBSCRIBED},
        {"unsubscribed", MessageType::UNSUBSCRIBED},
        {"info", MessageType::INFO},
        {"partial", MessageType::PARTIAL},
        {"update", MessageType::UPDATE},
        {"pong", MessageType::PONG}
    }};
    static constexpr auto type_lookup_map = LookupMap { type_values };

    /**
     * @brief Compile time evaluated map for assigning channel enum to new message
     * 
     */
    static constexpr std::array<std::pair<std::string_view, Channel>, 3> channel_values {{
        {"orderbook", Channel::ORDERBOOK},
        {"orders", Channel::ORDERS},
        {"fills", Channel::FILLS}
    }};
    static constexpr auto channel_lookup_map = LookupMap { channel_values };

    /**
     * @brief Base message type for the FTX exchange websocket messages.
     * All messages have a Type;
     */
    struct MessageBase {
        MessageType type;
    };

    /**
     * @brief Info messages can carry a code and message.
     * On code 20001, reconnection to the exchange should be attempted
     * 
     */
    struct InfoMessage : MessageBase {
        int code;
        std::string_view msg;
    };

    /**
     * @brief FTX Orderbook update message with bid and ask data
     * 
     */
    struct OrderbookMessage : MessageBase {
        std::string_view channel;
        std::string_view market;
        double time;
        int checksum;
        std::map<double, double> bids;
        std::map<double, double> asks;
    };

    /**
     * @brief Get the type from a websocket json message
     * 
     * @param str the json string
     * @return the message type enum
     */
    MessageType get_type(const std::string &str);

    /**
     * @brief Get the channel from a websocket json message
     * 
     * @param str the json string
     * @return the message channel enum
     */
    Channel get_channel(const std::string &str);

    /**
     * @brief Get the bids from the data field of an orderbook message
     * 
     * @param str the json string
     * @return the map of prices and values 
     */
    std::string get_bids_str(const std::string &str);
} // namespace Ayanami

#endif