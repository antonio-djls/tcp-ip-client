#include<iostream>
#include<sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main(){

  struct sockaddr_in servidor;
  int socket_escuta = socket(AF_INET, SOCK_STREAM, 0);

  if(socket_escuta == -1){
    std::cout << "Falha na criação do socket" << std::endl;
    return 0;
  }
  std::cout << "Socket Criado com sucesso " << std::endl;

  // Permite reutilizar a porta imediatamente mesmo se ela ainda estiver em TIME-WAIT
  // de uma conexão anterior (evita o erro "Falhou ao fazer o binding" ao reiniciar o server logo em seguida)
  int opt = 1;
  setsockopt(socket_escuta, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  // Configurando o Servidor
  servidor.sin_family = AF_INET; // Isso significa definir qual versão do protocolo TCP/IP será usado (AF_INET == Ipv4)
  servidor.sin_addr.s_addr = htonl(INADDR_ANY); // Associo um endereçamento ao socket, no caso o INADDR_ANY associa qualquer interface da máquina local ao socket
  // É óbvio se pensar, mas vale ressaltar que preciso associar um IP da máquina para fazer o socket funcionar
  servidor.sin_port = htons(8080); // Associo uma porta da interface/ip escolhida onde irei realizar a conexão TCP

  // No Binding associamos ao socket criado um ip e uma porta para executarmos a comunicação
  auto binding = bind(socket_escuta, (struct sockaddr*)&servidor, sizeof(servidor));
  if(binding == -1){
    std::cout << "Falhou ao fazer o binding " << std::endl;
    return 1;
  }
  std::cout << "Binding realizado com sucesso " << std::endl;

  // Para suportar múltiplas conexões o socket enfileira novas máquinas que estão tentando iniciar uma conexão com o socket
  // Permitindo que as conexões sejam enfileiradas e após responder a primeira máquinas as outras sãoa atendidas de acordo com a ordem da fila
  //
  int escutando_comunicao = listen(socket_escuta,10);

  if(escutando_comunicao == -1){
    std::cout << "Escuta do socket falhou " << std::endl;
  }else{
    std::cout << "Escuta do socket funcionando" << std::endl;
  }
  std::cout << "Esperando conexões ser feitas (Servidor esperando!!!) " << std::endl;
  // Aceitando conexões

  socklen_t  client_endereco_tamanho = sizeof(servidor);
  int socket_cliente = accept(socket_escuta,(struct sockaddr*)&servidor, &client_endereco_tamanho);
  if(socket_cliente == -1){
    std::cout << "Falha ao aceitar a comuniucação " << std::endl;
    close(socket_escuta);
    return 1;
  }
  std::cout << "Aceitou a conexão do client" << std::endl;

  // Para receber dados sobre o socket, preciso criar um buffer para armazenar os dados que vão ser recebidos
  // O buffer pode ser um array de char ou uma string completa

  const int tamanho_buffer = 1024;
  char buffer[tamanho_buffer] = {0};
 // Utilizo o recv() para receber os dados. E passo os requisitos para o socket
  int dados_recebidos = recv(socket_cliente,buffer,tamanho_buffer - 1,0);
  // O 0 é uma flag que pode ser passada, mas como não vou usar passo o zero

  if(dados_recebidos == -1){
    std::cout << "Erro ao receber os dados " << std::endl;
    close(socket_cliente);
    close(socket_escuta);
    return 0;
  }
  if(dados_recebidos == 0){
    std::cout << "Conexão fechada" << std::endl;
  }
  buffer[dados_recebidos] = '\0';
  std::cout <<  "Dados recebidos " << buffer << std::endl;
  close(socket_cliente);
  close(socket_escuta);
  return 0;
}
