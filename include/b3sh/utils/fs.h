#pragma once
#ifndef FS_H
#define FS_H

#include <string>
#include <vector>

namespace utils{
void write_history(std::vector<std::string> command_history);
std::vector<std::string> load_history();
} // namespace utils

#endif