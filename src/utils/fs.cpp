#include "b3sh/utils/fs.h"
#include "b3sh/utils/helper.h"

#include <fstream>
#include <iostream>

namespace utils{
void write_history(std::vector<std::string> command_history) {
    if (command_history.empty()) {
        return;
    }

    std::string path_to_history_file = utils::get_history_file_path();
    
    if (path_to_history_file.empty()) {
        return;
    }

    std::ofstream out(path_to_history_file, std::ios::app);

    if (!out) {
        return;
    }

    for (const auto& element : command_history) {
        out << element << '\n';
    }
}

std::vector<std::string> load_history() {
    std::vector<std::string> history;

     std::string path_to_history_file = utils::get_history_file_path();
    
    if (path_to_history_file.empty()) {
        return history;
    }

    std::ifstream file(path_to_history_file);

    if (!file) {
        return history;
    }

    std::string line;
    while(std::getline(file, line)) {
        history.push_back(line);
    }

    return history;
}
} // namespace utils
