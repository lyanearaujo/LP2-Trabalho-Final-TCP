cmake_minimum_required(VERSION 3.10)

project(ChatServerTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
find_package(Threads REQUIRED)

add_executable(test_logger 
    src/test_logger.cpp 
    src/logger.cpp
    include/colors.hpp
)
target_link_libraries(test_logger PRIVATE Threads::Threads)

add_executable(chat_server
    src/server_main.cpp
    src/server.cpp
    src/clienthandler.cpp
    src/chatroom.cpp      
    src/logger.cpp
    include/colors.hpp
)
target_link_libraries(chat_server PRIVATE Threads::Threads)

add_executable(chat_client
    src/client_main.cpp
    include/colors.hpp
)
target_link_libraries(chat_client PRIVATE Threads::Threads)

message(STATUS "Configuração do CMake concluída!")