# Trabalho Final LP2

## Compilar:
```
make
```

## Etapa 1: Teste de biblioteca de Log

### Executar:
```
cd /build
./test_logger
```
**O que esperar:**
O programa irá mostrar no console mensagens de 10 threads.
As mensagens aparecerão misturadas, mas cada linha estará completa e sem erros.

## Etapa 2: Protótipo Cliente/Servidor de Chat

### Executar:

#### 1. Inicie o servidor em um terminal:
```
# Estando na pasta 'build'
./chat_server
```

#### 2. Inicie os clientes em outro terminal:

**Opção A:** com o script (recomendado)

O scrip abre 3 clientes automaticamente.
```
# Estando na pasta raiz, dê permissão ao script (só na 1º vez)
chmod +x test_multiple_clients.sh

# Execute o script:
./test_multiple_clients.sh
```
**Opção B:** manualmente
```
# Estando na pasta 'build'
./chat_client
```

**O que esperar:** Com o script, vão ser abertos 3 clientes *(terminais)* automaticamente. Para testar o chat, fique à vontade em mandar qualquer mensagem para ver os clientes "conversando" entre si. Sem o script, terá que abrir um por um pelo comando acima.