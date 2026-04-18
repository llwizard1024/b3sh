#include "b3sh/utils/helper.h"

const char *const BUILTIN_COMMANDS[] = {"cd", "pwd", "export"};

namespace utils{
std::vector<std::string> split_string(const std::string &str, const char delimiter) {
    std::vector<std::string> result;
    size_t i = 0;
    const size_t n = str.length();

    while (i < n) {
        if (str[i] == delimiter) {
            ++i;
            continue;
        }

        if (str[i] == '"') {
            size_t start = i;
            ++i;
            while (i < n && str[i] != '"') {
                ++i;
            }

            if (i < n && str[i] == '"') {
                ++i;
            }

            result.push_back(str.substr(start, i - start));
        } else {
            size_t start = i;
            while (i < n && str[i] != delimiter) {
                ++i;
            }
            result.push_back(str.substr(start, i - start));
        }
    }

    return result;
}

bool is_builtin_command(const std::string &command) {
    for (auto &element : BUILTIN_COMMANDS) {
        if (element == command) {
            return true;
        }
    }

    return false;
}

void trim_string(std::string& str) {
    if (str.empty()) {
        return;
    }

    int start_index = 0, end_index = str.size();

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == ' ') {
            start_index++;
        } else {
            break;
        }
    }
    
    for (size_t i = str.size() - 1; i > 0; --i) {
        if (str[i] == ' ') {
            end_index--;
        } else {
            break;
        }
    }

    str.erase(0, start_index);
    str.erase(end_index);
}
} //namespace utils