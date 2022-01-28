#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP

#include <vector>
#include <functional>
#include <variant>
#include <any>
#include <iostream>

namespace Ayanami {

    // template<typename M, typename... Messages>
    // concept Message = std::enable_if<std::disjunction_v<std::is_same<M, Messages>...>>::value;

    /**
     * @brief Accepts parsed messages and dispaches thier data to the appropriate handler.
     * Messages can be queued using Ayanami::push_back_message or dispatched immediately with
     * operator().
     * 
     * This class probably didn't need this much templating as all message and handler types 
     * where known before it was written.
     * 
     */
    template<typename... Messages>
    class MessageBus {
        std::vector<std::variant<Messages...>> message_queue_;
        std::vector<std::any> handlers_;

    public:

        /**
         * @brief Distribute a message to appropriate handler callbacks
         * 
         * @tparam Message the type which must be the same as at least one of the templated
         * types of the messagebus
         * @param message the message
         */
        template<typename Message,
            typename std::enable_if<std::disjunction_v<std::is_same<Message, Messages>...>>::value>
        void operator()(const Message &message) {
            std::for_each(handlers_.begin(), handlers_.end(), [&message](auto handler){
                if (std::is_invocable_v<std::type_info(handler), Message>) {
                    handler(message);
                }
            });
        }

        /**
         * @brief Dispatch all queued messages to handler callbacks.
         * 
         */
        void dispatch() {
            while(!message_queue_.empty()) {
                this(message_queue_.front());

            }
        }

        /**
         * @brief Get the callables registered to the message bus
         * 
         * @return std::vector<std::any> 
         */
        std::vector<std::any> handlers() {
            return handlers_;
        }

        /**
         * @brief Get the message queue
         * 
         * @return the collection of messages
         */
        std::vector<std::variant<Messages...>> messages() {
            return message_queue_;
        }
    }; // MessageBus

    /**
     * @brief Assign a callback to a message bus.
     * The callback functor must accept at least one of the templated types of the message bus
     * 
     * @tparam Message the parameter type of the callback
     * @tparam Messages the templated types of the message bus
     * @param bus the message bus
     * @param callback the callback functor
     */
    template<typename Message, typename... Messages>
    void register_callback(MessageBus<Messages...> &bus, std::function<void(Message)> callback) {
        static_assert(std::disjunction_v<std::is_same<Message, Messages>...>);
        bus.handlers().push_back(callback);
    }

    /**
     * @brief Emplace a message to the back of the message bus queue
     * 
     * @tparam Message the message type wich must be the same as at least one of the templated
     * types of the message bus
     * @tparam Messages the template parameters of the message bus
     * @param bus the message bus
     * @param message the message
     */
    template<typename Message, typename... Messages>
    void emplace_message(MessageBus<Messages...> &bus, const Message &message) {
        static_assert(std::disjunction_v<std::is_same<Message, Messages>...>);
        bus.messages().push_back(message);
    } 
} // namespace Ayanami

#endif