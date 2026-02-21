#include <iostream>
#include "journal_api.h"

int main() {
    init_logger("log.txt", LogLevel::DEBUG);
    log_message("Journal Library initialized successfully.", LogLevel::INFO);
    set_default_level(LogLevel::ERROR);
    log_message("This debug message will not be logged.", LogLevel::DEBUG);
    return 0;   
}