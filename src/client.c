#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <unistd.h>
#include "config.h"

int main() {
  char *name;
  printf("Enter name:");
  scanf("%s", name);

  struct sockaddr_in addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  char buff[BUFF_SIZE] = {0};

  if (sock == -1) {
    perror("Error init socket\n");
  } else {
    printf("Socket init succses\n");
  }

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(8000);

  if (connect(sock, (const struct sockaddr*) &addr, sizeof(addr)) == -1){
    perror("Connection failed");
  } else {
    printf("Connection success\n");
  }

  char msg[MSG_SIZE] = {0};
  while (1) {
    printf(":");
    fgets(msg, MSG_SIZE, stdin);

    send(sock, msg, strlen(msg), 0);

    int bytes_read = read(sock, buff, sizeof(buff) - 1);
    if (bytes_read > 0) {
      buff[bytes_read] = '\0';
      printf("Сообщение сервера:%s\n", buff);
    }
  }
  close(sock);
  return 0;
}
