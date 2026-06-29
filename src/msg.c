#include "msg.h"
#include "config.h"
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

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

void log_msg(const char buff[32]){
  time_t time_now = time(NULL);
  struct tm *now = localtime(&time_now);

  log_data ld;

  char str_t[20];
  char str_d[20];

  strftime(str_t, sizeof(str_t),"%T", now);
  strftime(str_d, sizeof(str_d),"%D", now);
  // snprintf(ld.time, 64, "%s %s", str_t, str_d);

  FILE *fp = fopen("log.txt", "a");
  if(fp ==  NULL){
    perror("Error open file\n");
    return;
  }

  snprintf(ld.buff, 128, "%s %s %s", buff, str_t, str_d);
  fputs(ld.buff, fp);
  fclose(fp);
}
