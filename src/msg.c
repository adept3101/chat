#include "msg.h"
#include "config.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

void *get_msg(void *arg) {
  thread_data *data = (thread_data *)arg;
  char buff[BUFF_SIZE];

  while (1) {
    printf("$%s:", data->name);
    fgets(buff, BUFF_SIZE, stdin);
    send(data->sock, buff, strlen(buff), 0);
  }

  return NULL;
}

void *send_msg(void *arg) {
  thread_data *data = (thread_data *)arg;
  char buff[BUFF_SIZE];

  while (1) {
    int bytes_read = read(data->sock, buff, BUFF_SIZE - 1);
    // if (bytes_read > 0) {
      buff[bytes_read] = '\0';
      printf(":%s\n", buff);
    // }
  }

  return NULL;
}
