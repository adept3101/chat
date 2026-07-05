#include "sercli.h"
#include "msg.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>

void init_addr(struct sockaddr_in *addr, int port, char *ip) {

  addr->sin_family = AF_INET;
  addr->sin_addr.s_addr = inet_addr(ip);
  addr->sin_port = htons(port);
}

int create_server(int port, char *ip) {
  struct sockaddr_in addr, client_addr;
  thread_data data;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  int opt = 1;

  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

  init_addr(&addr, port, ip);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error bind\n");
    exit(1);
  } else {
    printf("Bind ok\n");
  }

  if (listen(sock, 1) == -1) {
    perror("Error listnening\n");
    exit(1);
  } else {
    printf("Listening og\n");
  }

  return accept(sock, (struct sockaddr *)&client_addr,
                (socklen_t *)&client_addr);
}

void connect_server(int port, char *ip) {
  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  init_addr(&addr, port, ip);

  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error connect\n");
    exit(1);
  } else {
    printf("Connect ok\n");
  }
}
