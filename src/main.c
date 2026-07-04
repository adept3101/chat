#include <netinet/in.h>
#include <stdio.h>
#include "sercli.h"
#include "msg.h"
#include "config.h"
#include <string.h>
#include <sys/socket.h>

int main() {
  thread_data data;
  char name[16];

  printf("Input name:");
  scanf("%s", name);

  strcpy(data.name, name);

  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  init_addr(&addr, PORT, IP);

  // return 0;
}
