#include "logger.hpp"
#include "colors.hpp"

Logger& Logger::getInstance()
{
    static Logger instance; // singleton
    return instance;
}

void Logger::log(LogLevel level, const std::string& message)
{
    std::lock_guard<std::mutex> guard(logMutex); // evita race condition no log

    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);

    std::string color = "";
    switch (level)
    {
        case LogLevel::INFO:    color = CYAN; break;
        case LogLevel::WARNING: color = YELLOW; break;
        case LogLevel::ERROR:   color = RED; break;
    }
    
    // imprime log com timestamp e nível
    std::cout << BOLD << "[" << std::put_time(std::localtime(&time_t_now), "%Y-%m-%d %H:%M:%S") << "] "
              << color <<"[" << levelToString(level) << "]: "
              << message << RESET << std::endl;
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