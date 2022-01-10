#ifndef AV_CORO_HPP
#define AV_CORO_HPP

#include <coroutine>
#include <variant>
#include <any>

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Experimental coroutine state machine implimentation for AV market making strategy
     * 
     */
    namespace av_coro {

        template<typename... events>
        struct event {};

        struct collect {};
        struct idle {};
        // what else ? ...

        /**
         * @brief Promise type of state machine
         * 
         */
        struct av_machine {
            struct promise_type {
                using handle = std::coroutine_handle<promise_type>;

                av_machine get_return_object() noexcept {
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

            ~av_machine() { coro.destroy(); }
            av_machine(const av_machine &) = delete;
            av_machine &operator=(const av_machine &) = delete;

            template<typename E>
            void on_event(E &&e) {
                auto& promise = coro.promise();
                if (promise.is_wanted_event(typeid(E))) {
                    promise.current_event = std::forward<E>(e);
                    coro();
                }
            }

        private:
            av_machine(std::coroutine_handle<promise_type> coro) : coro { coro } {}
            std::coroutine_handle<promise_type> coro;
        };

        av_machine get_av() {
            for(;;) {
                // collecting
                auto e = co_await event<collect, idle>{};
                if (std::holds_alternative<collect>(e)) {
                    std::cout << "Collecting\n";
                } else if (std::holds_alternative<idle>(e)) {
                    // idle
                    co_await event<collect>{};
                }
            }
        }
    } // namespace av
} // namespace ayanami

#endif