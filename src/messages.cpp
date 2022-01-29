#include "messages.hpp"

#include <fstream>
#include <sstream>

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