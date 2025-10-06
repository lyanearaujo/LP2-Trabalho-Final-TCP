#ifndef CHATROOM_HPP
#define CHATROOM_HPP

#include <vector>
#include <string>
#include <mutex>
#include <memory>
#include <deque>

class ClientHandler; 

// sala do chat que gerencia os clientes conectados
class ChatRoom
{
    public:
        ChatRoom();
        void addClient(std::shared_ptr<ClientHandler> client);
        void removeClient(std::shared_ptr<ClientHandler> client);
    
        // manda mensagem para todos menos o remetente
        void broadcastMessage(const std::string& message, int senderSocket);

        // histórico das mensagens
        void sendHistoryToClient(std::shared_ptr<ClientHandler> client);

    private:
        std::vector<std::shared_ptr<ClientHandler>> clients;
        std::mutex clientsMutex; // garante acesso seguro à lista de clientes acima

        std::deque<std::string> messageHistory;
        std::mutex historyMutex; // garante acesso seguro ao histórico de mensagens acima

        // filtro de mensagens proibidas
        std::vector<std::string> forbiddenWords;
        std::string filterMessage(const std::string& message);
};

#endif