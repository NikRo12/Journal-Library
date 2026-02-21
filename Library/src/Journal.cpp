#include <iostream>
#include <string>
#include <fstream>

#include <chrono>
#include <ctime>

#include <iomanip>
#include <sstream>

#include "Journal.h"

Journal::Journal(const std::string& p_filename, LogLevel p_default_level) 
    : filename(p_filename), default_level(p_default_level) {}

Journal::~Journal() {}

std::string Journal::getFilename() const {
    std::lock_guard<std::mutex> lock(Journal::mtx);
    return filename; 
}

LogLevel Journal::getDefaultLevel() const {
    std::lock_guard<std::mutex> lock(Journal::mtx);
    return default_level;
}

void Journal::write(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(Journal::mtx);
    if (level >= default_level || level == LogLevel::NONE) { 
        std::ofstream out(filename, std::ios::app);
        if (out.is_open()) {
            auto now = std::chrono::system_clock::now();
            auto in_time_t = std::chrono::system_clock::to_time_t(now);
            
            std::stringstream ss;
            ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

            if (level == LogLevel::NONE) {
                level = default_level;
            }

            std::string s_level;
            switch(level) {
                case LogLevel::DEBUG: s_level = "DEBUG"; break;
                case LogLevel::INFO:  s_level = "INFO";  break;
                case LogLevel::ERROR: s_level = "ERROR"; break;
                case LogLevel::NONE:  s_level = "NONE";  break;
            }

            out << "[" << ss.str() << "] [" << s_level << "] " << message << std::endl;

            if (out.fail()) {
                std::cerr << "Failed to write into log file '" << filename << "'" << std::endl;
            }
        } 
        
        else {
            std::cerr << "Failed to open log file: " << filename << std::endl;
        }
        
        out.close();
        if (out.fail()) {
            std::cerr << "Failed to close log file '" << filename << "'" << std::endl;
        }

        Journal::mtx.unlock();
    }
}

void Journal::set_level(LogLevel p_default_level) {
    std::lock_guard<std::mutex> lock(Journal::mtx);
    default_level = p_default_level;
}