#ifndef AV_CORO_HPP
#define AV_CORO_HPP

#include <coroutine>
#include <variant>
#include <any>
#include <map>
#include <string_view>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    template<typename... events>
    struct event {
        std::string_view str;
    };

    struct place {
        std::string_view str = "place";
    };

    struct modify {
        std::string_view str = "modify";
    };

    struct cancel {
        std::string_view str = "cancel";
    };

    /**
     * @brief Promise type of order machine
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

    order_machine get_order_machine() {
        // orders
        std::map<double, std::pair<double, int>> orders;
        for(;;) {
            auto ev = co_await event<place, modify, cancel>{};
            if (std::holds_alternative<modify>(ev)) {
                std::cout << "modifying\n";
            } else if (std::holds_alternative<place>(ev)) {
                std::cout << "placing\n";
            } else if (std::holds_alternative<cancel>(ev)) {
                std::cout << "cancelling\n";
            }
        }
    }
} // namespace ayanami

#endif