#include "b3sh/commands/cd.h"

#include <cerrno>
#include <iostream>
#include <unistd.h>

namespace {
void handle_errors(const std::string &command_name) {
    switch (errno) {
    case ENOENT:
        std::cerr << "cd: " << command_name << ": No such file or directory.\n";
        break;
    case EACCES:
        std::cerr << "cd: Permission denied.\n";
        break;
    case ENOTDIR:
        std::cerr << "cd: " << command_name << ": Not a directory.\n";
        break;
    case ENAMETOOLONG:
        std::cerr << "cd: The path argument is too long.\n";
        break;
    case ELOOP:
        std::cerr << "cd: Too many symbolic links.\n";
        break;
    default:
        std::cerr << errno << '\n';
        break;
    }
}
} // namespace

namespace commands {
void handle_cd(const std::vector<std::string>& commands) {
    const char *path;

    if (commands.size() > 1) {
        path = commands[1].c_str();
    } else {
        path = std::getenv("HOME");

        if (path == nullptr) {
            std::cerr << "HOME env var not setup.";
            return;
        }
    }

    if (chdir(path) != -1) {
        return;
    } else {
        handle_errors(commands[1]);
    }
}
} // namespace commands