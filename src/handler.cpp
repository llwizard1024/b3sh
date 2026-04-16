#include "b3sh/handler.h"
#include "b3sh/utils/helper.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <sys/wait.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <limits.h>
#include <vector>

int last_exit_code = 0;

void execute_command(const std::vector<std::string>& commands) {
    std::vector<char*> c_args;
    
    for (const auto& arg : commands) {
        c_args.push_back(const_cast<char*>(arg.c_str()));
    }
    
    c_args.push_back(nullptr);

    pid_t pid = fork();
    int status;

    if (pid < 0) {
        std::cout << "Fork not completed :(" << std::endl;
        return;
    }

    if (pid == 0) {
        execvp(c_args[0], c_args.data());

        _exit(127);
    } else {
        waitpid(pid, &status, 0);
    }

    if (WIFSIGNALED(status)) {
        std::cout << "Process killed by signal: " << strsignal(WTERMSIG(status)) << std::endl;
        return;
    }

    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 127) {
            std::cout << commands[0] << " command not found\n";
        } else {
            return;
        }
    }
}

void change_dir(const std::vector<std::string>& commands) {
    const char* path;

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
        switch (errno) {
            case ENOENT:
                std::cerr << "cd: " << commands[1] <<  ": No such file or directory.\n";
                break;
            case EACCES:
                std::cerr << "cd: Permission denied.\n";
                break;
            case ENOTDIR:
                std::cerr << "cd: " << commands[1] << ": Not a directory.\n";
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
}

void handle_export(const std::vector<std::string>& commands) {
    if (commands.size() > 1) {
        std::vector<std::string> params = split_string(commands[1], '=');

        if (params.size() == 2) {
            setenv(params[0].c_str(), params[1].c_str(), 1);
            return;
        }

        std::cerr << "Invalid params. Example [KEY=VALUE]\n";
    } else {
        int i = 0;
        while(__environ[i] != NULL) {
            std::cout << __environ[i] << std::endl;
            ++i;
        }
    }
}

void print_work_directory() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << cwd << std::endl;
    } else {
        std::cerr << "Error pwd." << std::endl;
    }
}

void processing_builtin_command(const std::vector<std::string>& commands) {
    if (commands[0] == "cd") {
        change_dir(commands);
    } else if (commands[0] == "pwd") {
        print_work_directory();
    } else if (commands[0] == "export") {
        handle_export(commands);
    }
}