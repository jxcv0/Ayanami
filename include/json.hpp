#ifndef JSON_HPP
#define JSON_HPP

#include <algorithm>
#include <map>

namespace Ayanami {

    /**
     * @brief Constexpr map for faster lookups
     * 
     * @tparam Key map key type
     * @tparam Value map value type
     * @tparam Size size of map must be known at compiletime
     */
    template<typename Key, typename Value, std::size_t Size>
    struct LookupMap {
        std::array<std::pair<Key, Value>, Size> data;

        [[nodiscard]] constexpr Value at(const Key &key) const {

            // linear search function is apparently faster for small maps than binary search
            const auto itr = std::find_if(data.begin(), data.end(), [&key](const auto &v) {
                return v.first == key;
            });

            if (itr != data.end()) {
                return itr->second;
            } else {
                throw std::range_error("Not Found");
            }
        }
    };

    /**
     * @brief Read .json file and return the contents as a string
     * 
     * @param file the path to the file
     * @return the json as a string
     */
    std::string file_to_string(const char* file);
} // namespace Ayanami

#endif