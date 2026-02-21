#include "journal_api.h"
#include "Journal.h"

Journal* g_journal = nullptr;

extern "C" {
    void init_logger(const char* filename, LogLevel default_level) {
        if (g_journal) delete g_journal;
        g_journal = new Journal(std::string(filename), default_level);
    }

    void log_message(const char* message, LogLevel level) {
        if (g_journal) {
            g_journal->write(std::string(message), level);
        }
    }

    void set_default_level(LogLevel new_level) {
        if (g_journal) {
            g_journal->set_level(new_level);
        }
    }
}