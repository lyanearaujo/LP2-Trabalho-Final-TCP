#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include <vector>
#include <string>
#include <mutex>
#include <memory> 

class ClientHandler; 

class ChatRoom
{
    public:
        void addClient(std::shared_ptr<ClientHandler> client);
        void removeClient(std::shared_ptr<ClientHandler> client);
    
        // envia uma mensagem de um cliente para todos os outros
        void broadcastMessage(const std::string& message, int senderSocket);

    private:
        std::vector<std::shared_ptr<ClientHandler>> clients;
        std::mutex clientsMutex; // Mutex para proteger a lista de clientes
};

#endif