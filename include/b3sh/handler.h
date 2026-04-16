#pragma once
#ifndef HANDLER_H
#define HANDLER_H

#include <vector>
#include <string>

extern int last_exit_code;

void execute_command(const std::vector<std::string>& commands);
void processing_builtin_command(const std::vector<std::string>& commands);

#endif