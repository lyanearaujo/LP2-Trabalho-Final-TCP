#!/bin/bash
# Script para simular múltiplos clientes se conectando ao servidor de chat.

NUM_CLIENTS=3
CLIENT_EXEC="./build/chat_client"

echo "Iniciando script de teste para $NUM_CLIENTS clientes..."

if [ ! -f "$CLIENT_EXEC" ]; then
    echo "Erro: O executável do cliente nao foi encontrado em $CLIENT_EXEC"
    echo "Por favor, compile o projeto primeiro (vá para a pasta 'build' e rode 'make')."
    exit 1
fi

echo "Iniciando $NUM_CLIENTS instancias do cliente em novos terminais..."

for (( i=1; i<=$NUM_CLIENTS; i++ ))
do
    gnome-terminal -- bash -c "$CLIENT_EXEC; exec bash" &
done

echo "Script concluído. Verifique as novas janelas de terminal."