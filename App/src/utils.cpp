#include "utils.h"

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, last - first + 1);
}

LogLevel choose_log_level(const std::string& str) {
    if (str == "DEBUG") return LogLevel::DEBUG;
    if (str == "INFO")  return LogLevel::INFO;
    if (str == "ERROR") return LogLevel::ERROR;
    
    return LogLevel::NONE;
}

void parseParams(std::string& filename, LogLevel& def, int argc, const char* argv[]) {
    if (argc < 2) {
        def = LogLevel::DEBUG;
        filename = "default.log";
        return;
    }
    
    filename = argv[1];
    
    if (argc >= 3) {
        def = choose_log_level(argv[2]);
    } else {
        def = LogLevel::DEBUG;
    }
}