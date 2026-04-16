#include "b3sh/utils/helper.h"

const char* const BUILTIN_COMMANDS[] = {
    "cd",
    "pwd",
    "export"
};

std::vector<std::string> split_string(const std::string& str, const char delimiter) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t pos = str.find(delimiter);

    while (pos != std::string::npos) {
        std::string token = str.substr(start, pos - start);
        if (!token.empty()) {
            result.push_back(token);
        }
        
        start = pos + 1;
        pos = str.find(delimiter, start);
    }

    std::string last_token = str.substr(start);
        if (!last_token.empty()) {
    result.push_back(last_token);
    }

    return result;
}

bool is_builtin_command(const std::string& command) {
    for (auto& element : BUILTIN_COMMANDS) {
        if (element == command) {
            return true;
        }
    }

    return false;
}