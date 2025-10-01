#include "server.hpp"
#include "logger.hpp"

int main()
{
    const int PORT = 8080;
    try
    {
        Server chatServer(PORT);
        chatServer.start();
    } catch (const std::exception& e)
    {
        Logger::getInstance().log(LogLevel::ERROR, "Opa! Deu erro critico no servidor: " + std::string(e.what()));
        return 1;
    }
    return 0;
}