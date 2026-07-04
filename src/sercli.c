#include "sercli.h"
// #include "config.h"
#include "msg.h"
#include <arpa/inet.h>
// #include <asm-generic/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

// void conn_opt() {
//   struct sockaddr_in addr;
//   int sock = socket(AF_INET, SOCK_STREAM, 0);
//
//   if (sock == -1) {
//     perror("Error init socket\n");
//     exit(1);
//   } else {
//     printf("Socket init\n");
//   }
//
//   addr.sin_family = AF_INET;
//   addr.sin_port = htons(PORT);
//   addr.sin_addr.s_addr = inet_addr(IP);
// }

void init_addr(struct sockaddr_in *addr, int port, char *ip) {
  // struct sockaddr_in addr;

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
  // memset(&addr, 0, sizeof(addr));
  
  init_addr(, int port, char *ip)

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

  // char *addr_server = inet_ntoa(addr.sin_addr);
  //
  // int c = sizeof(struct sockaddr_in);
  // int client = accept(sock, (struct sockaddr *)&addr, (socklen_t *)&c);
  // accept(int fd, struct sockaddr *restrict addr, socklen_t *restrict addr_len)
  
  // if (client == -1) {
  //   perror("Error accept\n");
  //   exit(1);
  // } else {
  //   printf("Accept ok\n");
  // }
  // data.sock = client;
  return accept(sock, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr);
}

void connect_server() {
  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  // connect(sock, (const struct sockaddr *)&addr, sizeof(addr));
  if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1){
    perror("Error connect\n");
    exit(1);
  } else {
    printf("Connect ok\n");
  }
}
