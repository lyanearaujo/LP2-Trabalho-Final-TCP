# Trabalho Final LP2

## Principais Funcionalidades
1. **Servidor Concorrente:** Capaz de lidar com múltiplos clientes simultaneamente, cada um em sua própria thread.
2. **Broadcast de Mensagens:** Mensagens são retransmitidas em tempo real para todos os usuários na sala.
3. **Histórico de Mensagens:** Novos usuários recebem as últimas 15 mensagens do chat assim que se conectam.
4. **Logging Thread-Safe:** Todos os eventos importantes do servidor são registrados de forma segura usando uma biblioteca de log customizada.
5. **Script de Teste:** Um script (`test_multiple_clients.sh`) para simular múltiplos usuários de forma automática.

## Como Compilar:
O projeto utiliza CMake. Para compilar, execute os seguintes comandos a partir da raiz do projeto:
```
cd /build
make clean
make
```
Isso irá gerar os executáveis `chat_server` e `chat_client` no diretório `build/`

## Como Executar
Você precisará de pelo menos dois terminais.

### 1. Inicie o Servidor:
Em um terminal, execute o servidor. Ele ficará aguardando conexões.
```
cd /build
./chat_server
```

### 2. Inicie os Clientes:
Para simular a conversa, você pode usar o script de teste que abre 3 clientes automaticamente.
```
# Na pasta raiz, dê permissão ao script (só na primeira vez)
chmod +x test_multiple_clients.sh

# Em outro terminal, execute o script
./test_multiple_clients.sh
```

### Teste da Biblioteca de Log
Para executar o teste de concorrência da biblioteca de logging (desenvolvida na Etapa 1), use o comando:
```
cd /build
./test_logger
```