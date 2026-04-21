#include "b3sh/terminal/input.h"

#include <iostream>

namespace {
void move_cursor_right(int n) {
    if (n > 0) {
        std::cout << "\033[" << n << "C" << std::flush;
    }
}

void move_cursor_left(int n) {
    if (n > 0) {
        std::cout << "\033[" << n << "D" << std::flush;
    }
}
}

namespace terminal{
void clear_line() {
    std::cout << "\033[2K\rb3sh> " << std::flush;
}

std::string handle_input(std::vector<std::string>& history) {
    std::string buffer;
    size_t cursor_pos = 0;
    size_t history_index = history.size();

    // Enable raw mode
    TermiosGuard tg;
    tg.setRawMode();

    while(true) {
        char symbol;

        if (read(STDIN_FILENO, &symbol, 1) == -1) {
            break;
        }
        
        // Key: enter
        if (symbol == '\n' || symbol == '\r') {
            break;
        } else if (symbol == '\b' || symbol == 0x7f) {
            if (cursor_pos > 0) {
                buffer.erase(cursor_pos - 1, 1);
                cursor_pos--;

                clear_line();
                std::cout << buffer << std::flush;

                move_cursor_left(buffer.size() - cursor_pos);
            }
        } else if (symbol == '\033') {
            char seq[2];
            if (read(STDIN_FILENO, &seq[0], 1) == -1) continue;
            if (read(STDIN_FILENO, &seq[1], 1) == -1) continue;

            if (seq[0] == '[') {
                switch (seq[1]) {
                    case 'C': // right arrow
                        if (cursor_pos < buffer.size()) {
                            cursor_pos++;
                            move_cursor_right(1);
                        }
                        break;
                    case 'D': // left arrow
                        if (cursor_pos > 0) {
                            cursor_pos--;
                            move_cursor_left(1);
                        }
                        break;
                    case 'A': // up arrow
                        if (history_index > 0) {
                            --history_index;
                            buffer = history[history_index];
                            cursor_pos = buffer.size();

                            clear_line();
                            std::cout << buffer << std::flush;
                        }
                        break;
                    case 'B': // down arrow
                        if (history_index < history.size()) ++history_index;
                        if (history_index < history.size()) {
                            buffer = history[history_index];
                            cursor_pos = buffer.size();

                            clear_line();
                            std::cout << buffer << std::flush;
                        }
                        break;
                }
            }
        } else if (symbol == '\x03') {
            buffer.clear();
            cursor_pos = 0;
            history_index = history.size();
            clear_line();
            continue;
        } else if (symbol == '\x04') {
            if (buffer.empty()) {
                buffer = "exit";
                return buffer;
            }
        } else if (symbol >= 32 && symbol <= 126) { // ASCII symbols
            buffer.insert(cursor_pos, 1, symbol);
            cursor_pos++;

            clear_line();
            std::cout << buffer << std::flush;
            move_cursor_left(buffer.size() - cursor_pos);
        }
    }

    return buffer;
}
} // namespace terminal