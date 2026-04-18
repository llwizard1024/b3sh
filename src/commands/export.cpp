#include "b3sh/commands/export.h"
#include "b3sh/utils/helper.h"

#include <iostream>
#include <unistd.h>

namespace {
void show_all_env_var() {
    int i = 0;
    while (__environ[i] != NULL) {
        std::cout << __environ[i] << std::endl;
        ++i;
    }
}
}

namespace commands {
void handle_export(const std::vector<std::string> &commands) {
    if (commands.size() > 1) {
        std::vector<std::string> params = utils::split_string(commands[1], '=');

        if (params.size() == 2) {
            setenv(params[0].c_str(), params[1].c_str(), 1);
            return;
        }

        std::cerr << "Invalid params. Example [KEY=VALUE]\n";
    } else {
        show_all_env_var();
    }
}
} // namespace commands