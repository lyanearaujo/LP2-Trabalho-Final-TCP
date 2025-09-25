#ifndef SERVER_HPP
#define SERVER_HPP

#include "chatroom.hpp"
#include <netinet/in.h>

class Server
{
    public:
        Server(int port);
        ~Server();

        void start();

    private:
        void setup(); // configura o socket
        void acceptConnections(); // aceita novos clientes

        int port;
        int serverSocket;
        struct sockaddr_in serverAddr;
        ChatRoom chatroom; //o servidor "possui" a sala de chat
};

#endif