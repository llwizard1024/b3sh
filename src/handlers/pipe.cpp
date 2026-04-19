#include "b3sh/handlers/pipe.h"
#include "b3sh/utils/helper.h"

#include <cstring>
#include <iostream>
#include <array>
#include <unistd.h>
#include <sys/wait.h>

namespace handlers{
void execute_pipe(const std::vector<std::string>& pipe_commands) {
    std::vector<std::array<int, 2>> pipes_fd;
    std::vector<pid_t> pids;

    // Create and init pipe fd
    for (size_t i = 0; i < pipe_commands.size() - 1; ++i) {
        std::array<int, 2> fds;
        
        if (pipe(fds.data()) == -1) {
            std::cerr << "Error pipe init";
            return;
        }

        pipes_fd.push_back(fds);
    }

    // Run commands in sub process
    for (size_t i = 0; i < pipe_commands.size(); ++i) {
        std::vector<std::string> commands = utils::split_string(pipe_commands[i], ' ');

        // Setup flags for STDIN, STDOUT for subprocess
        int in_fd = (i == 0) ? STDIN_FILENO : pipes_fd[i-1][0];
        int out_fd = (i == pipe_commands.size() - 1) ? STDOUT_FILENO : pipes_fd[i][1];

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
            dup2(in_fd, STDIN_FILENO);
            dup2(out_fd, STDOUT_FILENO);

            //Close for EOF
            for (size_t j = 0; j < pipes_fd.size(); ++j) {
                close(pipes_fd[j][0]);
                close(pipes_fd[j][1]);
            }

            execvp(c_args[0], c_args.data());

            _exit(127);
        }

        pids.push_back(pid);
    }

    // Close again for all EOF
    for (size_t i = 0; i < pipes_fd.size(); ++i) {
        close(pipes_fd[i][0]);
        close(pipes_fd[i][1]);
    }

    // Run all process and wait pipe pids
    for (size_t i = 0; i < pids.size(); ++i) {
        int status;
        waitpid(pids[i], &status, 0);
    }
}
} //namespace handlers