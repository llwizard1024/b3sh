#pragma once
#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <string>

std::vector<std::string> split_string(const std::string& str, const char delimiter);
bool is_builtin_command(const std::string& command);

#endif