#include "config.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void *send_msg(void *arg, char name[], char buff[], int sock) {
  printf("$%s:", name);
  fgets(buff, BUFF_SIZE, stdin);
  send(sock, buff, strlen(buff), 0);

  return NULL;
}

void *get_msg(void *arg, char name[], char buff[], int sock) {
  int bytes_read = read(sock, buff, BUFF_SIZE - 1);
  if (bytes_read > 0) {
    buff[bytes_read] = '\0';
    printf(":%s\n", buff);
  }

  return NULL;
}

int main() {

  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  char buff[BUFF_SIZE] = {0};
  pthread_t thr1, thr2;

  if (sock == -1) {
    perror("Error init socket\n");
  } else {
    printf("Socket init succses\n");
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(8000);

  if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Connection failed");
  } else {
    printf("Connection success\n");
  }

  char name[32];
  printf("Enter name:");
  fgets(name, sizeof(name), stdin);
  name[strcspn(name, "\n")] = '\0';
  snprintf(buff, sizeof(buff), "%s\n", name);
  send(sock, buff, strlen(buff), 0);

  int name_read = read(sock, buff, sizeof(buff) - 1);
  if (name_read > 0) {
    buff[name_read] = '\0';

    printf("server name:%s\n", buff);
  }

  // while (1) {
  //   printf("$%s:", name);
  //   fgets(buff, BUFF_SIZE, stdin);
  //
  //   send(sock, buff, strlen(buff), 0);
  //
  //   int bytes_read = read(sock, buff, sizeof(buff) - 1);
  //   if (bytes_read > 0) {
  //     buff[bytes_read] = '\0';
  //     printf("Сообщение сервера:%s\n", buff);
  //   }
  // }

  close(sock);
  // free(name);

  return 0;
}
