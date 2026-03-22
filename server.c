#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct sockaddr_in addr, _client;
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  char buffer[1024] = {0};

  if (sock == -1) {
    perror("Failed init socket\n");
    exit(EXIT_FAILURE);
  } else {
    printf("Socket init ok\n");
  }

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htons(INADDR_ANY); // inet_addr
  addr.sin_port = htons(8000);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error bind\n");
    exit(EXIT_FAILURE);
  } else {
    printf("bind ok\n");
  }

  if (listen(sock, 1) == -1) {
    perror("Listening failed\n");
    close(sock);
    exit(EXIT_FAILURE);
  } else {
    printf("Listening...\n");
  }

  char *addr_server = inet_ntoa(addr.sin_addr);
  printf("ip_address of server: %s:%d\n", addr_server, ntohs(addr.sin_port));

  int client;
  int c = sizeof(struct sockaddr_in);

  // while (1) {
  //   client = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
  //   char *addr_client = inet_ntoa(_client.sin_addr);
  //   int port = htons(_client.sin_port);
  //
  //   if (client == -1) {
  //     perror("Error client\n");
  //     exit(EXIT_FAILURE);
  //   } else {
  //     printf("connected with client\n");
  //     printf("ip-address of client: %s:%d\n", addr_client, port);
  //   }
  // }
  client = accept(sock, (struct sockaddr *)&client, (socklen_t *)&c);
  char *addr_client = inet_ntoa(_client.sin_addr);

  if (client == -1) {
    perror("Accept failed\n");
    exit(1);
  } else {
    printf("Connected with client\n");
    printf("ip-address of client: %s:%d\n", addr_client, _client.sin_port);
  }

  int bytes_read = read(client, buffer, sizeof(buffer) - 1);
  if (bytes_read > 0) {
    buffer[bytes_read] = '\0';
    printf("Сообщение клиента:%s", buffer);
  }

  char msg[64] = {0};

  printf(":");
  fgets(msg, 64, stdin);

  send(client, msg, strlen(msg), 0);

  close(client);
  close(sock);

  return 0;
}
