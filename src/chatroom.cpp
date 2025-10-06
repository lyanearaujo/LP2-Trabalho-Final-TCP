#include "chatroom.hpp"
#include "clienthandler.hpp"
#include "logger.hpp"
#include <algorithm>

const size_t MAX_HISTORY_SIZE = 15;

void ChatRoom::addClient(std::shared_ptr<ClientHandler> client)
{
    // bloquinho para garantir que o lock seja liberado o mais rápido possível
    {
        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(client);
    }
    Logger::getInstance().log(LogLevel::INFO, "Pessoa " + std::to_string(client->getSocket()) + " entrou! Bem vindo(a)! :D ");
    sendHistoryToClient(client); // manda o histórico de mensagens para o novo cliente
}

void ChatRoom::removeClient(std::shared_ptr<ClientHandler> client)
{
    std::lock_guard<std::mutex> lock(clientsMutex);

    // remove cliente da lista comparando socket
    clients.erase(std::remove_if(clients.begin(), clients.end(), [&](const std::shared_ptr<ClientHandler>& c)
                {return c->getSocket() == client->getSocket();}), clients.end());

    Logger::getInstance().log(LogLevel::INFO, "Pessoa " + std::to_string(client->getSocket()) + " foi embora. Tchauzinho! :] ");
}

void ChatRoom::broadcastMessage(const std::string& message, int senderSocket)
{
    std::scoped_lock lock(clientsMutex, historyMutex);
    Logger::getInstance().log(LogLevel::INFO, "Broadcast da mensagem do socket " + std::to_string(senderSocket));

    messageHistory.push_back(message);
    if (messageHistory.size() > MAX_HISTORY_SIZE)
    {
        messageHistory.pop_front(); // histórico com tamanho fixo
    }

    // envia mensagem para todos menos o remetente
    for (const auto& client : clients)
    {
        if (client->getSocket() != senderSocket)
        {
            client->sendMessage(message);
        }
    }
}

void ChatRoom::sendHistoryToClient(std::shared_ptr<ClientHandler> client)
{
    std::lock_guard<std::mutex> lock(historyMutex);
    Logger::getInstance().log(LogLevel::INFO, "Enviando historico para Pessoa " + std::to_string(client->getSocket()));
    
    for (const auto& msg : messageHistory)
    {
        // prefixo para deixar claro que é mensagem antiga
        client->sendMessage("[HISTÓRICO] " + msg);
    }
}