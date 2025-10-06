#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include "colors.hpp"

void receive_messages(int clientSocket)
{
    char buffer[4096];
    while (true)
    {
        memset(buffer, 0, 4096);
        int bytesReceived = recv(clientSocket, buffer, 4096, 0);
        
        if (bytesReceived <= 0)
        {
            std::cout << BOLD << RED << "\n>> Voce foi desconectado :(" << RESET << std::endl;
            break; // sai do loop se perdeu conexão
        }

        std::cout << std::string(buffer, bytesReceived) << std::endl;
    }
}

void send_messages(int clientSocket)
{
    std::string message;
    while (true)
    {
        std::getline(std::cin, message);

        if (message.empty())
        {
            continue; // ignora mensagens vazias
        }

        int sendResult = send(clientSocket, message.c_str(), message.length(), 0);
        if (sendResult < 0)
        {
            std::cout << BOLD << RED << "Ops, nao consegui enviar sua mensagem :/" << RESET << std::endl;
            break;
        }
    }
}

int main()
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        std::cerr << BOLD << RED << "Ops, nao deu para criar socket :/" << RESET << std::endl;
        return 1;
    }

    std::string ipAddress = "127.0.0.1"; 
    int port = 8080;        
    
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ipAddress.c_str(), &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cerr << BOLD << RED << "Ops, nao foi possivel conectar ao servidor :/" << RESET << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << BOLD << BLUE << "Voce esta conectado :D! Digite suas mensagens abaixo:" << RESET << std::endl;

    // cria threads separadas, uma para enviar e a outra para receber
    std::thread receiverThread(receive_messages, clientSocket);
    std::thread senderThread(send_messages, clientSocket);

    receiverThread.join();
    senderThread.join();

    close(clientSocket);
    return 0;
}