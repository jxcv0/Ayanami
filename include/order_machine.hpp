#ifndef AV_CORO_HPP
#define AV_CORO_HPP

#include <coroutine>
#include <variant>
#include <any>
#include <map>
#include <string_view>
#include <iostream>

namespace Ayanami {

    /**
     * this is an absurd and slow way of implimenting a bit of code that manages orders.
     * but it looks cool
     */

    struct EventBase {
        std::map<double, std::pair<double, int>> orders;
    };

    // TODO - pass in av_state through events
    struct Collect : EventBase {};
    struct Init : EventBase {};
    struct Run : EventBase {};
    struct Close : EventBase {};

    template<typename... events>
    struct event {};

    /**
     * @brief Promise type
     * 
     */
    struct OrderMachine {
        struct promise_type {
            using handle = std::coroutine_handle<promise_type>;

            OrderMachine get_return_object() noexcept {
                return { handle::from_promise(*this) };
            }

            std::suspend_never Initial_suspend() const noexcept { return {}; }
            std::suspend_always final_suspend() const noexcept { return {}; }

            template<typename... E>
            auto await_transform(event<E...>) noexcept {
                is_wanted_event = [](const std::type_info& type)->bool {
                    return ((type == typeid(E)) || ...);
                };

                struct awaitable {
                    bool await_ready() const noexcept { return false; }
                    void await_suspend(handle) noexcept {}

                    std::variant<E...> await_resume() const {
                        std::variant<E...> event;
                        (void) ((current_event->type() == typeid(E) ?
                            (event = std::move(*std::any_cast<E>(current_event))
                            , true) : false) || ...);
                        return event;
                    }
                    const std::any *current_event;
                };
                return awaitable { &current_event };
            }

            void return_void() noexcept {}
            void unhandled_exception() noexcept {}

            std::any current_event;
            bool (*is_wanted_event)(const std::type_info&) = nullptr;
        };

        ~OrderMachine() { coro.destroy(); }
        OrderMachine(const OrderMachine &) = delete;
        OrderMachine &operator=(const OrderMachine &) = delete;

        template<typename E>
        void on_event(E &&e) {
            auto& promise = coro.promise();
            if (promise.is_wanted_event(typeid(E))) {
                promise.current_event = std::forward<E>(e);
                coro();
            }
        }

    private:
        OrderMachine(std::coroutine_handle<promise_type> coro) : coro { coro } {}
        std::coroutine_handle<promise_type> coro;
    };

    OrderMachine get_order_machine(const std::map<double, std::pair<double, int>>& orders) {
        for(;;) {
            // Collect
            auto e = co_await event<Collect>{};
            if (std::holds_alternative<Collect>(e)) {
                auto s = std::get<Collect>(e);
                std::cout << std::to_string(s.orders[100].second) << "\n";
                // TODO - await data

                // Init
                auto e = co_await event<Init>{};
                if(std::holds_alternative<Init>(e)) {
                    auto s = std::get<Init>(e);
                    // place all orders in map

                    // Run
                    auto e = co_await event<Run>{};
                    if(std::holds_alternative<Run>(e)) {
                        auto s = std::get<Run>(e);
                        // compare map orders to b and a
                        // shuffle orders

                        // Close
                        auto e = co_await event<Close>{};
                        if (std::holds_alternative<Close>(e)) {
                            auto s = std::get<Close>(e);
                            // cancel all orders 
                            // Close position
                            goto end;
                        }
                    }
                } 
            }
        } end: std::cout << "End.\n";
    }
} // namespace ayanami

#endif