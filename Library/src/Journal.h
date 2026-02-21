#ifndef JOURNAL_H
#define JOURNAL_H

#include <string>
#include <mutex>
#include "journal_api.h"

class Journal {
private: 
    std::string filename;
    LogLevel default_level;
    mutable std::mutex mtx;
public: 
    Journal(const std::string& filename, LogLevel default_level);
    ~Journal();

    std::string getFilename() const;
    LogLevel getDefaultLevel() const;

    void write(const std::string& message, LogLevel level);
    void set_level(LogLevel new_level);
};

#endif // JOURNAL_H