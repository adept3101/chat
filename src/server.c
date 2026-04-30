#include "config.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct sockaddr_in addr, _client;
  char buffer[BUFF_SIZE] = {0};
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

  char *name;
  printf("Enter name:");
  scanf("%s", name);

  char *addr_server = inet_ntoa(addr.sin_addr);
  printf("ip_address of server: %s:%d\n", addr_server, ntohs(addr.sin_port));
  printf("User:%s\n", name);

  pthread_t thr_res;

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


  while (1) {
    int bytes_read = read(client, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';
      // printf("%s:%s", client_name, buffer);
    }

    char msg[MSG_SIZE] = {0};

    printf(":");
    fgets(msg, MSG_SIZE, stdin);
    send(client, msg, strlen(msg), 0);
  }

  close(client);
  close(sock);

  return 0;
}
