#ifndef CLIENTHANDLER_HPP
#define CLIENTHANDLER_HPP

#include "chatroom.hpp"
#include <string>
#include <memory> 

class ChatRoom; 

class ClientHandler : public std::enable_shared_from_this<ClientHandler>
{
    public:
        ClientHandler(int socket, ChatRoom& room);
        ~ClientHandler();

        void startHandling(); // Inicia o loop de leitura de mensagens do cliente
        void sendMessage(const std::string& message); // Envia uma mensagem para este cliente
        int getSocket() const;

    private:
        void handleMessages(); // O método que rodará na thread

        int clientSocket;
        ChatRoom& chatRoom; // Referência para a sala de chat
        std::string username;
};

#endif 