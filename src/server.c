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
#include "msg.h"

int main() {
  struct sockaddr_in addr, _client;
  char buff[BUFF_SIZE] = {0};
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  pthread_t thr1, thr2;
  thread_data data;
  int opt = 1;

  if (sock == -1) {
    perror("Error init sock");
  } else {
    printf("Successfully init sock\n");
  }

  data.sock = sock;
  strcpy(data.name, "serva4ok");

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

  pthread_create(&thr1, NULL, (void *) send_msg, &data);
  pthread_create(&thr2, NULL, (void *) get_msg, &data);

  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  close(client);
  close(sock);

  return 0;
}
