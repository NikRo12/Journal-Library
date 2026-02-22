#ifndef UTILS_H
#define UTILS_H

#include <string>
#include "journal_api.h"

std::string trim(const std::string& str);
LogLevel choose_log_level(const std::string& str);
void parseParams(std::string& filename, LogLevel& def, int argc, const char* argv[]);

#endif // UTILS_H