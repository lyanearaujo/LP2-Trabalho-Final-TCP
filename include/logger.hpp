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
}; // define os níveis do log

class Logger
{
    public:
        // o singleton requer que o construtor de cópia e o operador de atribuição
        // sejam deletados para evitar múltiplas instâncias.
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        /**
         * @brief Retorna a única instância da classe Logger.
         * * @return Logger& Uma referência para a instância do Logger.
         */
        static Logger& getInstance();

        /**
         * @brief Loga uma mensagem com um determinado nível.
         * A função é thread-safe.
         * * @param level O nível do log (INFO, WARNING, ERROR).
         * @param message A mensagem a ser logada.
         */
        void log(LogLevel level, const std::string& message);

    private:
        Logger() {}
        std::mutex logMutex; // garante que apenas uma thread escreva no log por vez
        std::string levelToString(LogLevel level); // converte loglevel -> string
};

#endif