#include<iostream>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<cstring>

int main(){

  struct sockaddr_in servidor;
  int socket_cliente;
  socket_cliente = socket(AF_INET, SOCK_STREAM, 0);

  if(socket_cliente == -1){
    std::cout << "Falha na criação do socket" << std::endl;
    return 1;
  }
  std::cout << "Socket criado com sucesso " << std::endl;

  // Configurando o endereço do servidor ao qual quero me conectar
  servidor.sin_family = AF_INET;
  servidor.sin_port = htons(8080); // mesma porta que o server está escutando
  inet_pton(AF_INET, "127.0.0.1", &servidor.sin_addr); // IP do server (localhost)

  // connect() tenta estabelecer a conexão TCP com o server (que precisa já estar em listen/accept)
  int conexao = connect(socket_cliente, (struct sockaddr*)&servidor, sizeof(servidor));
  if(conexao == -1){
    std::cout << "Falha ao conectar ao servidor " << std::endl;
    return 1;
  }
  std::cout << "Conectado ao servidor com sucesso " << std::endl;

  // Setando o buffer para poder enviar a mensagem
  const int tamanho_do_buffer = 1024;
  char buffer[tamanho_do_buffer] = {0};
  std::cout << "Digite o que será enviado pelo socket " << std::endl;
  std::cin.getline(buffer, tamanho_do_buffer);

  send(socket_cliente,buffer, strlen(buffer), 0);
  close(socket_cliente);

  return 0;
}
