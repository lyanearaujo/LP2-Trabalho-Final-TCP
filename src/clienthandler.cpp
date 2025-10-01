#include "clienthandler.hpp"
#include "logger.hpp"
#include <thread>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

ClientHandler::ClientHandler(int socket, ChatRoom& room) : clientSocket(socket), chatRoom(room) {}

ClientHandler::~ClientHandler()
{
    close(clientSocket); // garante que o socket fecha ao destruir o objeto
}

void ClientHandler::startHandling()
{
    // cada cliente roda em uma thread separada
    std::thread clientThread(&ClientHandler::handleMessages, this);
    clientThread.detach();
}

void ClientHandler::handleMessages()
{
    char buffer[4096];
    while (true)
    {
        memset(buffer, 0, 4096);
        int bytesReceived = recv(clientSocket, buffer, 4096, 0);

        if (bytesReceived <= 0)
        {
            Logger::getInstance().log(LogLevel::WARNING, "Cliente " + std::to_string(clientSocket) + " desconectou. Tchauu!");
            break;
        }
        // repassa a mensagem para todos os clientes do chatroom
        chatRoom.broadcastMessage(std::string(buffer, bytesReceived), clientSocket);
    }
    // remove cliente do chatroom ao desconectar
    chatRoom.removeClient(shared_from_this());
}

void ClientHandler::sendMessage(const std::string& message)
{
    send(clientSocket, message.c_str(), message.length(), 0);
}

int ClientHandler::getSocket() const
{
    return clientSocket;
}