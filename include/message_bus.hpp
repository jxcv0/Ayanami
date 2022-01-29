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
         * @brief Distribute all messages in the queue to the visitors.
         * 
         * @param visitor the callback visitor
         */
        void operator()(auto visitor) {
            while (!queue_.empty()) {
                std::visit(visitor, queue_.front());
                queue_.erase(queue_.begin());
            }
        }

        /**
         * @brief Distribute a message to callback visitor
         * 
         * @tparam Message the message type. Must be the same as at least one of the templated
         * types of the bus.
         * @param visitor the callback visitor 
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
         * @tparam Message the message type. Must be the same as at least one of the templated
         * types of the bus.
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
} // namespace Ayanami

#endif