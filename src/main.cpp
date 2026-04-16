#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include "b3sh/utils/helper.h"
#include "b3sh/handler.h"

int main() {
    while (true) {
        std::string command;

        std::cout << "b3sh> ";
        if (!std::getline(std::cin, command)) {
            std::cout << std::endl;
            break;
        }

        std::vector<std::string> commands = split_string(command, ' ');


        if (commands.empty()) {
            continue;
        }

        if (commands[0] == "exit") {
            break;
        }
        
        if (is_builtin_command(commands[0])) {
            processing_builtin_command(commands);
        } else {
            execute_command(commands);
        }
    }

    return 0;
}