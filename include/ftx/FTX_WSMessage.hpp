#ifndef FTX_WSMESSAGE_HPP
#define FTX_WSMESSAGE_HPP

#include <string>

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
         * @brief An ftx message
         * 
         */
        struct FTX_WSMessage{
            std::string channel;
            std::string market;
            std::string type;
            std::string code;
            std::string message;
            std::string data;
        };

        /**
         * @brief Parse a raw message int an FTX_WSMessage struct
         * 
         * @param ftx_msg the struct to reuse
         * @param msg the message string from the websocket
         */
        void parse(FTX_WSMessage ftx_msg, std::string msg);

        /**
         * @brief Reset the fields of a message for reuse
         * 
         * @param msg the message to rested
         */
        void reset(FTX_WSMessage ftx_msg);
        
    } // namespace ftx
} // namespace ayanami

#endif