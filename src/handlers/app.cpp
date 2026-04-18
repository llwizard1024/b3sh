#include "b3sh/handlers/app.h"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace handlers {
void execute_app(const std::vector<std::string> &commands) {
    if (commands.empty()) {
        std::cerr << "execute_command: empty command\n";
        return;
    }

    std::vector<char*> c_args;
    c_args.reserve(commands.size() + 1);
    for (const auto &arg : commands) {
        c_args.push_back(const_cast<char*>(arg.c_str()));
    }
    c_args.push_back(nullptr);

    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "Fork failed: " << std::strerror(errno) << '\n';
        return;
    }

    if (pid == 0) {
        execvp(c_args[0], c_args.data());

        _exit(127);
    } else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            std::cerr << "waitpid failed: " << std::strerror(errno) << '\n';
            return;
        }

        if (WIFSIGNALED(status)) {
            std::cerr << "Process killed by signal: " << strsignal(WTERMSIG(status))
                      << '\n';
        } else if (WIFEXITED(status) && WEXITSTATUS(status) == 127) {
            std::cerr << commands[0] << ": command not found\n";
        }
    }
}
} // namespace handlers