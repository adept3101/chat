#include "config.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct sockaddr_in addr, _client;
  char buff[BUFF_SIZE] = {0};
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock == -1) {
    perror("Error init sock");
  } else {
    printf("Successfully init sock\n");
  }

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(PORT);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error bind\n");
    exit(1);
  } else {
    printf("bind ok\n");
  }

  if (listen(sock, 1) == -1) {
    perror("Listening failed\n");
    close(sock);
    exit(1);
  } else {
    printf("Listening...\n");
  }


  char *addr_server = inet_ntoa(addr.sin_addr);
  printf("ip_address of server: %s:%d\n", addr_server, ntohs(addr.sin_port));

  int c = sizeof(struct sockaddr_in);
  int client = accept(sock, (struct sockaddr *)&_client, (socklen_t *)&c);
  char *addr_client = inet_ntoa(_client.sin_addr);

  if (client == -1) {
    perror("Accept failed\n");
    exit(1);
  } else {
    printf("Connected with client\n");
    printf("ip-address of client: %s:%d\n", addr_client,
           ntohs(_client.sin_port));
  }

  char name[32];
  printf("Enter name: ");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';
  snprintf(buff, sizeof(buff), "%s\n", name);

  ssize_t res = send(client, buff, strlen(buff), 0);
  if (res == -1){
    perror("Send failed\n");
    exit(1);
  } else {
    printf("Send success\n");
  }
  
  int name_read = read(client, buff, sizeof(buff) - 1);
  if (name_read > 0) {
    buff[name_read] = '\0';

    printf("client name:%s\n", buff);
  }

  while (1) {
    int bytes_read = read(client, buff, sizeof(buff) - 1);

    if (bytes_read > 0) {
      buff[bytes_read] = '\0';
      // printf("%s:%s", client_name, buff);
    }

    printf("$%s:", name);
    fgets(buff, BUFF_SIZE, stdin);
    send(client, buff, strlen(buff), 0);
  }

  close(client);
  close(sock);

  return 0;
}
