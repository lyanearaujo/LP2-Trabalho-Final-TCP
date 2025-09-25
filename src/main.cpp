#include <iostream>
#include <thread>  
#include <vector>
#include <string>
#include "logger.hpp" 

void log_worker(int threadId)
{
    for (int i = 0; i < 20; ++i)
    {
        std::string message = "Thread " + std::to_string(threadId) + " registrando a mensagem " + std::to_string(i);
        Logger::getInstance().log(LogLevel::INFO, message);
    }
}

int main()
{
    Logger::getInstance().log(LogLevel::INFO, "Teste de log iniciado");

    const int NUM_THREADS = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        threads.emplace_back(log_worker, i);
    }

    Logger::getInstance().log(LogLevel::INFO, "Todas as " + std::to_string(NUM_THREADS) + " threads foram criadas/iniciadas");

    for (auto& t : threads)
    {
        t.join();
    }

    Logger::getInstance().log(LogLevel::ERROR, "Todas as threads concluiram");

    return 0;
}