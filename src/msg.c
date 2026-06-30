#include "msg.h"
// #include "config.h"
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <time.h>

pthread_mutex_t m;

// pthread_mutex_init(&m, NULL);

void *send_msg(void *arg) {
  thread_data *data = (thread_data *)arg;
  char buff[BUFF_SIZE];
  
  pthread_mutex_init(&m, NULL);
  pthread_mutex_lock(&m);
  while (1) {
    printf("\n$%s:", data->name);
    fgets(buff, BUFF_SIZE, stdin);
    send(data->sock, buff, strlen(buff), 0);

    log_msg(buff, "send_log.txt");
  }
  
  pthread_mutex_unlock(&m);
  pthread_mutex_destroy(&m);
  return NULL;
}

void *get_msg(void *arg) {
  thread_data *data = (thread_data *)arg;
  char buff[BUFF_SIZE];

  pthread_mutex_init(&m, NULL);
  pthread_mutex_lock(&m);
  while (1) {
    // int bytes_read = read(data->sock, buff, BUFF_SIZE - 1);
    int bytes_read = recv(data->sock, buff, BUFF_SIZE - 1, 0);
    if (bytes_read <= 0) {
      printf("Disconnected\n");
      break;
    }

    buff[bytes_read] = '\0';
    printf("\n1:%s\n", buff);
    log_msg(buff, "get_log.txt");
  }

  pthread_mutex_unlock(&m);
  pthread_mutex_destroy(&m);

  return NULL;
}

void log_msg(const char *buff, char *file){
  time_t time_now = time(NULL);
  struct tm *now = localtime(&time_now);

  char str_t[20];
  char str_d[20];

  strftime(str_t, sizeof(str_t),"%T", now);
  strftime(str_d, sizeof(str_d),"%D", now);

  FILE *fp = fopen(file, "a");
  if(fp ==  NULL){
    perror("Error open file\n");
    return;
  }

  fprintf(fp, "%s %s %s\n", buff, str_t, str_d);
  fputs(buff, fp);
  fclose(fp);
}
