#pragma once
#include <vector>
#include <string>
#include <regex>
namespace string_help {
    std::vector<std::string> split(const std::string& s, const std::string& rgx_str = "\\s+") {
        std::vector<std::string> elems;
        std::regex rgx(rgx_str);

        std::sregex_token_iterator iter(s.begin(), s.end(), rgx, -1);
        std::sregex_token_iterator end;

        while (iter != end) {
            elems.push_back(*iter);
            ++iter;
        }
        return elems;
    }
    template <typename T> std::string n2hexstr(T w, size_t hex_len = sizeof(T) << 1) {
        static const char* digits = "0123456789ABCDEF";
        std::string rc(hex_len, '0');
        for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
            rc[i] = digits[(w >> j) & 0x0f];
        return rc;
    }
}