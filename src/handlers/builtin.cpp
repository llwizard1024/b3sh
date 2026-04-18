#include "b3sh/handlers/builtin.h"
#include "b3sh/commands/cd.h"
#include "b3sh/commands/export.h"
#include "b3sh/commands/pwd.h"

namespace handlers{
void execute_builtin(const std::vector<std::string> &commands) {
    if (commands[0] == "cd") {
        commands::handle_cd(commands);
        return;
    }

    if (commands[0] == "pwd") {
        commands::handle_pwd();
    }

    if (commands[0] == "export") {
        commands::handle_export(commands);
    }
}
} //namespace handlers