#include "b3sh/commands/pwd.h"

#include <limits.h>
#include <unistd.h>

#include <iostream>

namespace commands {
void handle_pwd() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        std::cout << cwd << std::endl;
    } else {
        std::cerr << "Error pwd." << std::endl;
    }
}
} // namespace commands