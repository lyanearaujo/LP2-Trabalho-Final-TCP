#ifndef SERVER_HPP
#define SERVER_HPP

#include "chatroom.hpp"
#include <netinet/in.h>

// classe principal do servidor
class Server
{
    public:
        Server(int port);
        ~Server();

        void start();

    private:
        void setup();
        void acceptConnections();

        int port;
        int serverSocket;
        struct sockaddr_in serverAddr;
        ChatRoom chatroom; // cada servidor tem uma sala
};

#endif