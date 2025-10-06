#include "server.hpp"
#include "clienthandler.hpp"
#include "logger.hpp"
#include <stdexcept>
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port) : port(port), serverSocket(-1)
{
    Logger::getInstance().log(LogLevel::INFO, "Servidor iniciando, só um minutinho...");
    setup();
}

Server::~Server()
{
    if (serverSocket != -1)
    {
        close(serverSocket);
    }
    Logger::getInstance().log(LogLevel::INFO, "Servidor finalizado. Ate mais!!");
}

void Server::setup()
{
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    {
        throw std::runtime_error("Ops, nao consegui criar o socket do servidor. :/");
    }

    int opt = 1;
    if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        throw std::runtime_error("Ops, deu erro ao configurar SO_REUSEADDR. :/");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; 
    serverAddr.sin_port = htons(port); 

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        throw std::runtime_error("Ops, deu erro no bind do socket. :/");
    }

    Logger::getInstance().log(LogLevel::INFO, "Servidor configurado na porta " + std::to_string(port));
}

void Server::start()
{
    if (listen(serverSocket, 10) < 0)
    { 
        throw std::runtime_error("Ops, não consegui colocar o servidor em modo de escuta. :/");
    }

    acceptConnections(); // loop infinito de conexões
}

void Server::acceptConnections()
{
    while (true)
    {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        if (clientSocket < 0)
        {
            Logger::getInstance().log(LogLevel::ERROR, "Opa, não consegui aceitar nova conexao. :/");
            continue; 
        }

        // cria handler para o cliente e o adiciona ao chatroom
        auto clientHandler = std::make_shared<ClientHandler>(clientSocket, chatroom);
        chatroom.addClient(clientHandler);
        clientHandler->startHandling();
    }
}