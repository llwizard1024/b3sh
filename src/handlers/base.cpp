#include "b3sh/handlers/base.h"
#include "b3sh/handlers/app.h"
#include "b3sh/handlers/pipe.h"
#include "b3sh/utils/helper.h"
#include "b3sh/handlers/builtin.h"

#include <vector>
#include <string>

namespace handlers{
void process_input(const std::string& line) {
    std::vector<std::string> pipes = utils::split_string(line, '|');

    if (pipes.size() < 2) {
        std::vector<std::string> commands = utils::split_string(line, ' ');
        
        if (utils::is_builtin_command(commands[0])) {
            handlers::execute_builtin(commands);
            return;
        } else {
            handlers::execute_app(commands);
            return;
        }
    }
    
    handlers::execute_pipe(pipes);
}
} // namespace handlers