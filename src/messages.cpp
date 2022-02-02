#include "messages.hpp"

#include <fstream>
#include <sstream>
#include <iostream> // delete
#include <algorithm>

/**
 * @brief Read .json file and return the contents as a string
 * 
 * @param file the path to the file
 * @return the json as a string
 */
std::string Ayanami::Messages::file_to_string(const char* file) {
    std::ifstream jsonFile(file);
    std::stringstream buffer;
    buffer << jsonFile.rdbuf();
    return buffer.str();
}

/**
 * @brief Get the type from a websocket message string literal
 * 
 * @param str the string literal
 * @return the message type enum
 */
Ayanami::Messages::MessageType Ayanami::Messages::get_type(const std::string &str) {
    size_t start_pos, end_pos;
    if ((start_pos = str.find("type")) != std::string::npos) {
        start_pos += 8;
        end_pos = start_pos;
        while (str.substr(end_pos, 1) != "\"") {
            end_pos++;
        }
        return Ayanami::Messages::type_lookup_map[str.substr(start_pos, end_pos - start_pos)];
    } else {
        throw std::out_of_range("\"type\" not found in json string");
    }
}

/**
 * @brief Get the channel from a websocket json message
 * 
 * @param str the json string
 * @return the message channel enum
 */
Ayanami::Messages::Channel Ayanami::Messages::get_channel(const std::string &str) {
    size_t start_pos, end_pos;
    if ((start_pos = str.find("channel")) != std::string::npos) {
        start_pos += 11;
        end_pos = start_pos;
        while (str.substr(end_pos, 1) != "\"") {
            end_pos++;
        }
        return Ayanami::Messages::channel_lookup_map[str.substr(start_pos, end_pos - start_pos)];
    } else {
        throw std::out_of_range("\"channel\" not found in json string");
    }
}

/**
 * @brief Get the bids array from an orderbook update message
 * 
 * @param str the json string
 * @return the values of the message delimited with ','
 */
void Ayanami::Messages::isolate_bids(std::string &str) {
    size_t nested_depth = 0;
    size_t start_pos, end_pos, pos, prev = 0;
    if ((start_pos = str.find("bids")) != std::string::npos) {
        start_pos += 7;
        end_pos = start_pos;
        while (true) {
            if (str[end_pos] == '[') {
                nested_depth++;
            } else if (str[end_pos] == ']') {
                nested_depth--;
            }

            if (nested_depth == 0 && str[end_pos] == ',')
                break;

            end_pos++;
        }
        str = str.substr(start_pos + 1, (end_pos - start_pos) - 2);

    } else {
        throw std::out_of_range("\"bids\" not found in json string");
    }
}

/**
 * @brief Get the asks array from an orderbook update message
 * 
 * @param str the json string
 * @return the values of the message delimited with ','
 */
void Ayanami::Messages::isolate_asks(std::string &str) {
    size_t nested_depth = 0;
    size_t start_pos, end_pos, pos, prev = 0;
    if ((start_pos = str.find("asks")) != std::string::npos) {
        start_pos += 7;
        end_pos = start_pos;
        while (true) {
            if (str[end_pos] == '[') {
                nested_depth++;
            } else if (str[end_pos] == ']') {
                nested_depth--;
            }

            if (nested_depth == 0 && str[end_pos] == ',')
                break;

            end_pos++;
        }

        str = str.substr(start_pos + 1, (end_pos - start_pos) - 2);
    } else {
        throw std::out_of_range("\"asks\" not found in json string");
    }
}