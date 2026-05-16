#include "config.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
// #include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "msg.h"

int main() {
  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  char buff[BUFF_SIZE] = {0};
  thread_data data;
  pthread_t thr1, thr2;

  if (sock == -1) {
    perror("Error init socket\n");
  } else {
    printf("Socket init succses\n");
  }

  data.sock = sock;
  strcpy(data.name, "negroni");

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr(IP);
  addr.sin_port = htons(8000);

  if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Connection failed");
  } else {
    printf("Connection success\n");
  }

  pthread_create(&thr1, NULL, send_msg, &data);
  pthread_create(&thr2, NULL, get_msg, &data);

  pthread_join(thr1, NULL);
  pthread_join(thr2, NULL);

  close(sock);

  return 0;
}
