#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <mutex>   
#include <chrono>   
#include <iomanip>  

// níveis de log (p/ debug)
enum class LogLevel
{
    INFO,
    WARNING,
    ERROR
};

// logger simples em formato de singleton
class Logger
{
    public:
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& getInstance();

        void log(LogLevel level, const std::string& message);

    private:
        Logger() {}
        std::mutex logMutex; // evita conflito de escrita
        std::string levelToString(LogLevel level); // converte enum em string
};

#endif