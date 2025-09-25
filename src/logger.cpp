#include "logger.hpp"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> guard(logMutex); 

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    std::cout << "[" << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S") << "] "
              << "[" << levelToString(level) << "]: "
              << message << std::endl;
}

std::string Logger::levelToString(LogLevel level)
{
    switch (level)
    {
        case LogLevel::INFO:    return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR:   return "ERROR";
        default:                return "UNKNOWN";
    }
}