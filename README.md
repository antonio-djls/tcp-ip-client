# TCP Server & Client

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/7/71/TCP_Three-Way_Handshake.svg" alt="TCP Three-Way Handshake" width="500"/>
</p>

Implementação básica de um **servidor TCP** e um **cliente TCP** em C++, usando a API de sockets. O cliente envia uma mensagem digitada pelo usuário ao servidor através de um socket na interface loopback.

## Estrutura do projeto

| Arquivo | Descrição |
|---|---|
| `main.cpp` | Servidor TCP: cria o socket, faz `bind()` na porta 8080 (com `SO_REUSEADDR`), entra em `listen()` com fila de até 10 conexões, aceita um cliente com `accept()` e imprime a mensagem recebida via `recv()`. |
| `cliente.cpp` | Cliente TCP: cria o socket, conecta em `127.0.0.1:8080` com `connect()`, lê uma linha do teclado e envia ao servidor com `send()`. |

## Fluxo da comunicação

```
Servidor: socket() → bind() → listen() → accept() → recv() → close()
Cliente:  socket() → connect() → send() → close()
```

## Como compilar e executar

```bash
# Compilar
g++ main.cpp -o main.exe
g++ cliente.cpp -o cliente.exe

# Terminal 1 — iniciar o servidor
./main.exe

# Terminal 2 — iniciar o cliente e digitar a mensagem
./cliente.exe
```

