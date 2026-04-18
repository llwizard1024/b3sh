#include "b3sh/utils/helper.h"
#include "b3sh/handlers/base.h"
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    while (true) {
        std::string command;

        std::cout << "b3sh> ";
        if (!std::getline(std::cin, command)) {
            std::cout << std::endl;
            break;
        }
        
        utils::trim_string(command);

        if (command.empty()) {
            continue;
        }

        if (command == "exit") {
            break;
        }

        handlers::process_input(command);
    }

    return 0;
}