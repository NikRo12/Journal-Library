#ifndef JOURNAL_API_H
#define JOURNAL_API_H

enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    ERROR = 2
};

extern "C" {
    void init_logger(const char* filename, LogLevel default_level);
    void log_message(const char* message, LogLevel level);
    void set_default_level(LogLevel new_level);
}

#endif // JOURNAL_API_H