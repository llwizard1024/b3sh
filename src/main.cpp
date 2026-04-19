#include "b3sh/utils/helper.h"
#include "b3sh/handlers/base.h"
#include "b3sh/terminal/input.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

int main() {
    std::vector<std::string> command_history;

    while (true) {
        terminal::clear_line();
        std::string command = terminal::handle_input(command_history);
        
        utils::trim_string(command);

        if (command.empty()) {
            continue;
        }

        if (command == "exit") {
            std::cout << '\n' << std::flush;
            break;
        }

        if (!command.empty() && (command_history.empty() || command_history.back() != command)) {
            command_history.push_back(command);
        }

        std::cout << '\n';
        handlers::process_input(command);
    }

    return 0;
}