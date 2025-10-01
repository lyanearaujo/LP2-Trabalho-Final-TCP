#include "chatroom.hpp"
#include "clienthandler.hpp"
#include "logger.hpp"
#include <algorithm>

void ChatRoom::addClient(std::shared_ptr<ClientHandler> client)
{
    std::lock_guard<std::mutex> lock(clientsMutex); // trava para evitar concorrência
    clients.push_back(client);
    Logger::getInstance().log(LogLevel::INFO, "Cliente " + std::to_string(client->getSocket()) + " adicionado a sala.");
}

void ChatRoom::removeClient(std::shared_ptr<ClientHandler> client)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    // remove cliente da lista comparando socket
    clients.erase(std::remove_if(clients.begin(), clients.end(), [&](const std::shared_ptr<ClientHandler>& c)
                {return c->getSocket() == client->getSocket();}), clients.end());
    
    Logger::getInstance().log(LogLevel::INFO, "Cliente " + std::to_string(client->getSocket()) + " removido da sala.");
}

void ChatRoom::broadcastMessage(const std::string& message, int senderSocket)
{
    std::lock_guard<std::mutex> lock(clientsMutex);
    Logger::getInstance().log(LogLevel::INFO, "Broadcast da mensagem do socket " + std::to_string(senderSocket));

    // envia mensagem para todos menos o remetente
    for (const auto& client : clients)
    {
        if (client->getSocket() != senderSocket)
        {
            client->sendMessage(message);
        }
    }
}