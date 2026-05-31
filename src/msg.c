#include "msg.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void *send_msg(void *arg) {
  thread_data *data = (thread_data *)arg;
  char buff[BUFF_SIZE];

  while (1) {
    printf("$%s:", data->name);
    fgets(buff, BUFF_SIZE, stdin);
    send(data->sock, buff, strlen(buff), 0);
  }

  return NULL;
}

void *get_msg(void *arg) {
  thread_data *data = (thread_data *)arg;
  char buff[BUFF_SIZE];

  while (1) {
    // int bytes_read = read(data->sock, buff, BUFF_SIZE - 1);
    int bytes_read = recv(data->sock, buff, BUFF_SIZE - 1, 0);
    if (bytes_read <= 0) {
      printf("Disconnected\n");
      break;
    }
    buff[bytes_read] = '\0';
    printf("1:%s\n", buff);
    log_msg(buff);
  }

  return NULL;
}

void log_msg(char buff[32]){
  FILE *fp = fopen("log.txt", "a");
  fputs(buff, fp);
  fclose(fp);
}
