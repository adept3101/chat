#include <netinet/in.h>
#include <stdio.h>
#include "sercli.h"
#include "msg.h"
#include "config.h"
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>

int main() {
  thread_data data;
  char name[16];

  printf("Input name:");
  scanf("%s", name);

  strcpy(data.name, name);

  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  init_addr(&addr, PORT, IP);
  create_server(PORT, IP);

  pthread_t thr_get, thr_send;

  pthread_create(&thr_send, NULL, send_msg, &data);
  pthread_create(&thr_get, NULL, get_msg, &data);

  pthread_join(thr_send, NULL);
  pthread_join(thr_get, NULL);

  // return 0;
}
