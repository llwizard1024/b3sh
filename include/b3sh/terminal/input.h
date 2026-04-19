#pragma once
#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>
#include <termios.h>
#include <unistd.h>

namespace terminal{
void clear_line();
std::string handle_input(std::vector<std::string>& history);

class TermiosGuard{
    int _fd;
    struct termios _original;
public:
    TermiosGuard(int fd = STDIN_FILENO) : _fd(fd) {
        tcgetattr(_fd, &_original);
    }

    ~TermiosGuard() {
        tcsetattr(_fd, TCSANOW, &_original);
    }

    void setRawMode() {
        struct termios raw = _original;
        cfmakeraw(&raw);
        tcsetattr(_fd, TCSANOW, &raw);
    }
};
} // namespace terminal

#endif
