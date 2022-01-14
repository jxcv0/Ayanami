#ifndef MSG_BASE_HPP
#define MSG_BASE_HPP

/**
 * @brief Cryprocurrency trading library
 * 
 */
namespace ayanami {

    /**
     * @brief Interface for excracting relevant data (price, time, size) from a trade message
     * 
     * @tparam T derived class
     */
    template<typename T>
    class trade_msg_base {
        std::static_cast<T*>(this)->price();
        std::static_cast<T*>(this)->time();
        std::static_cast<T*>(this)->size();
    };

    /**
     * @brief Interface for excracting relevant data (price, time, size) from an orderbook message.
     * This method assumes the API removes entries from the orderbook by sending an order size of
     * 0.
     * 
     * @tparam T derived class
     */
    template<typename T>
    class orderbook_msg_base {
        std::static_cast<T*>(this)->price();
        std::static_cast<T*>(this)->time();
        std::static_cast<T*>(this)->size();
    };

    /**
     * @brief Interface for extracting relevant data from an order message. 
     * 
     * @tparam T 
     */
    template<typename T>
    class orders_msg_base {
        // TODO  
    };
} // namespace ayanami
#endif