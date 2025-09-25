#include "logger.hpp"

Logger& Logger::getInstance()
{
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> guard(logMutex); // garante liberação do mutex mesmo tendo exceções

    // obter o timestamp atual
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    
    // output será: [TIMESTAMP] [NÍVEL]: MENSAGEM
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