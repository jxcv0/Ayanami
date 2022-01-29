#include "messages.hpp"

#include <fstream>
#include <sstream>
#include <iostream> // delete

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