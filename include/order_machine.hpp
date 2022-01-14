#ifndef AV_CORO_HPP
#define AV_CORO_HPP

#include <coroutine>
#include <variant>
#include <any>
#include <map>
#include <string_view>
#include <iostream>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * this is an absurd and slow way of implimenting a bit of code that manages orders.
     * but it looks cool
     */

    struct event_base {
        std::map<double, std::pair<double, int>> orders;
    };

    // TODO - pass in av_state through events
    struct collect : event_base {};
    struct init : event_base {};
    struct run : event_base {};
    struct close : event_base {};

    template<typename... events>
    struct event {};

    /**
     * @brief Promise type
     * 
     */
    struct order_machine {
        struct promise_type {
            using handle = std::coroutine_handle<promise_type>;

            order_machine get_return_object() noexcept {
                return { handle::from_promise(*this) };
            }

            std::suspend_never initial_suspend() const noexcept { return {}; }
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

        ~order_machine() { coro.destroy(); }
        order_machine(const order_machine &) = delete;
        order_machine &operator=(const order_machine &) = delete;

        template<typename E>
        void on_event(E &&e) {
            auto& promise = coro.promise();
            if (promise.is_wanted_event(typeid(E))) {
                promise.current_event = std::forward<E>(e);
                coro();
            }
        }

    private:
        order_machine(std::coroutine_handle<promise_type> coro) : coro { coro } {}
        std::coroutine_handle<promise_type> coro;
    };

    order_machine get_order_machine(const std::map<double, std::pair<double, int>>& orders) {
        for(;;) {
            // collect
            auto e = co_await event<collect>{};
            if (std::holds_alternative<collect>(e)) {
                auto s = std::get<collect>(e);
                std::cout << std::to_string(s.orders[100].second) << "\n";
                // TODO - await data

                // init
                auto e = co_await event<init>{};
                if(std::holds_alternative<init>(e)) {
                    auto s = std::get<init>(e);
                    // place all orders in map

                    // run
                    auto e = co_await event<run>{};
                    if(std::holds_alternative<run>(e)) {
                        auto s = std::get<run>(e);
                        // compare map orders to b and a
                        // shuffle orders

                        // close
                        auto e = co_await event<close>{};
                        if (std::holds_alternative<close>(e)) {
                            auto s = std::get<close>(e);
                            // cancel all orders 
                            // close position
                            goto end;
                        }
                    }
                } 
            }
        } end: std::cout << "End.\n";
    }
} // namespace ayanami

#endif