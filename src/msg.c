#include "msg.h"
#include "config.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

char get_msg(int sock, char buff[]) {

  int bytes_read = read(sock, buff, sizeof(buff) - 1);

  if (bytes_read > 0) {
    buff[bytes_read] = '\0';
    // printf("%s:%s", client_name, buffer);
  }
  return buff[bytes_read];
}

char send_msg(char *usr, int sock, char buff[]) {

  printf("$%s:", usr);
  fgets(buff, BUFF_SIZE, stdin);

  send(sock, buff, strlen(buff), 0);
}
