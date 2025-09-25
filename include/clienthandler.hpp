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

        void startHandling();
        void sendMessage(const std::string& message);
        int getSocket() const;

    private:
        void handleMessages(); 
        int clientSocket;
        ChatRoom& chatRoom; 
        std::string username;
};

#endif 