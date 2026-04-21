#pragma once
#ifndef COMPLETION_H
#define COMPLETION_H

#include <unordered_set>
#include <string>
#include <vector>

namespace terminal{
std::unordered_set<std::string> get_all_commands();
std::vector<std::string> get_all_matches(const std::string& str);
} // namespace terminal

#endif