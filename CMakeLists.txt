cmake_minimum_required(VERSION 3.10)

project(ChatServerTest VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
find_package(Threads REQUIRED)

add_executable(test_logger 
    src/main.cpp 
    src/logger.cpp
)

target_link_libraries(test_logger PRIVATE Threads::Threads)
message(STATUS "Configuração do CMake para test_logger concluída!")