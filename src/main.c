#include "config.h"
#include "msg.h"
#include "sercli.h"
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// enum Command { SERVER, CLIENT, UNKNOWN };
//
// enum Command select_command(char *str) {
//   if (strcpy(str, "server") == 0) return SERVER;
//   if (strcpy(str, "client") == 0) return  CLIENT;
//   return UNKNOWN;
// }

int main() {
  thread_data data;
  char name[16];

  printf("Input name:");
  scanf("%s", name);

  strcpy(data.name, name);

  
  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  init_addr(&addr, PORT, IP);

  int choose;
  printf("=====MENU=====\n");
  printf("Server: 1\nClient: 2\n");
  printf(":");
  scanf("%d", &choose);

  switch(choose) {
    case 1:
      data.sock = create_server(PORT, IP);

    case 2:
      data.sock = connect_server(PORT, IP);

    default:
      printf("Unavailable\n");
  }
  // data.sock = create_server(PORT, IP);

  pthread_t thr_get, thr_send;

  pthread_create(&thr_send, NULL, send_msg, &data);
  pthread_create(&thr_get, NULL, get_msg, &data);

  pthread_join(thr_send, NULL);
  pthread_join(thr_get, NULL);

  close(data.sock);

  // return 0;
}
