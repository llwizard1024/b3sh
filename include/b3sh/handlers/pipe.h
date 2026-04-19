#pragma once
#ifndef PIPE_H
#define PIPE_H

#include <string>
#include <vector>

namespace handlers{
void execute_pipe(const std::vector<std::string>& pipe_commands);
} //namespace handlers

#endif