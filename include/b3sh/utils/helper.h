#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <string>
#include <vector>

namespace utils{
std::vector<std::string> split_string(const std::string &str,
                                      const char delimiter);
bool is_builtin_command(const std::string &command);
void trim_string(std::string& str);
} // namepsace utils

#endif