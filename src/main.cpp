#include <iostream>
#include <thread>  
#include <vector>
#include <string>
#include "logger.hpp" 

/**
 * @brief Esta é a função que cada thread executará.
 * Ela simula um "trabalhador" que realiza alguma tarefa e registra seu progresso.
 * @param threadId Um identificador único para a thread, para que possamos ver quem está logando.
 */
void log_worker(int threadId)
{
    for (int i = 0; i < 20; ++i)
    {
        // mensagem única para cada log
        std::string message = "Thread " + std::to_string(threadId) + " registrando a mensagem numero " + std::to_string(i);

        // acessa o logger singleton e chama o método log
        Logger::getInstance().log(LogLevel::INFO, message);
    }
}

int main()
{
    Logger::getInstance().log(LogLevel::INFO, "Aplicacao de teste de log concorrente iniciada.");

    const int NUM_THREADS = 10;
    std::vector<std::thread> threads;

    for (int i = 0; i < NUM_THREADS; ++i)
    {
        // O `emplace_back` constrói a thread diretamente no vetor.
        // Passamos a função `log_worker` e seu argumento `i` para a nova thread.
        threads.emplace_back(log_worker, i);
    }

    Logger::getInstance().log(LogLevel::INFO, "Todas as " + std::to_string(NUM_THREADS) + " threads foram criadas e iniciadas.");

    // Aguarda todas as threads terminarem
    // O `join()` é um ponto de sincronização. O programa principal (a thread main)
    // vai parar aqui e esperar que cada thread da lista termine sua execução.
    for (auto& t : threads)
    {
        t.join();
    }

    Logger::getInstance().log(LogLevel::ERROR, "Todas as threads concluiram. Finalizando a aplicacao.");

    return 0;
}