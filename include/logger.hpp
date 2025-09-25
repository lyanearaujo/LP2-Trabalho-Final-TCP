#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <mutex>   
#include <chrono>   
#include <iomanip>  

enum class LogLevel
{
    INFO,
    WARNING,
    ERROR
};

class Logger
{
    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& getInstance();

        void log(LogLevel level, const std::string& message);

    private:
        Logger() {}
        std::mutex logMutex;
        std::string levelToString(LogLevel level);
};

#endif