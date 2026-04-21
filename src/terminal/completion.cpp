#include "b3sh/terminal/completion.h"
#include "b3sh/utils/helper.h"

#include <filesystem>

using namespace std::filesystem;

namespace terminal{
std::unordered_set<std::string> get_all_commands() {
    std::unordered_set<std::string> commands;

    // Load builtin commands
    for (size_t i = 0; i < BUILTIN_COMMANDS.size(); ++i) {
        commands.insert(BUILTIN_COMMANDS[i]);
    }

    // Load system commands
    char* path_env = std::getenv("PATH");

    if (path_env == nullptr) {
        return commands;
    }

    std::vector<std::string> path_env_dirs = utils::split_string(path_env, ':');

    for (const auto& dir : path_env_dirs) {
        for (const auto& element : directory_iterator(dir)) {
            if (!element.is_directory()) {
                commands.insert(element.path().filename().string());
            }
        }
    }
    
    // Load from current path
    for (auto& element : directory_iterator(current_path())) {
        if (element.is_directory()) {
            commands.insert(element.path().filename().string() + '/');
        } else {
            commands.insert(element.path().filename().string());
        }
    }

    return commands;
}

std::vector<std::string> get_all_matches(const std::string& str) {
    std::unordered_set<std::string> all_commands = get_all_commands();
    std::vector<std::string> command_matches;

    for (const auto& element : all_commands) {
        if (element.substr(0, str.size()) == str) {
            command_matches.push_back(element);
        }
    }

    return command_matches;
}
} // namespace terminal