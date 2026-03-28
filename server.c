#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// typedef struct {
//   int socket;
// } client_data;
//
// void *get_msg(void *arg) {
//   client_data *data = (client_data *)arg;
//   int client_sock = data->socket;
//   char buffer[1024] = {0};
//
//   while (1) {
//     size_t bytes_read = read(client_sock, buffer, sizeof(buffer) - 1);
//     if (bytes_read > 0) {
//       buffer[bytes_read] = '\0';
//       printf("Сообщение клиента:%s", buffer);
//     }
//   }
//
//   close(client_sock);
//   free(data);
//   return NULL;
// }

int main() {
  struct sockaddr_in addr, _client;
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);
  char buffer[1024] = {0};

  if (sock == -1) {
    perror("Failed init socket\n");
    exit(1);
  } else {
    printf("Socket init ok\n");
  }

  int opt = 1;
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  memset(&addr, 0, sizeof(addr));

  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY; // inet_addr
  addr.sin_port = htons(8000);

  if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Error bind\n");
    exit(1);
  } else {
    printf("bind ok\n");
  }

  if (listen(sock, 1) == -1) {
    perror("Listening failed\n");
    close(sock);
    exit(1);
  } else {
    printf("Listening...\n");
  }

  char *addr_server = inet_ntoa(addr.sin_addr);
  printf("ip_address of server: %s:%d\n", addr_server, ntohs(addr.sin_port));

  pthread_t thr_res;

  int client;
  int c = sizeof(struct sockaddr_in);

  client = accept(sock, (struct sockaddr *)&_client, (socklen_t *)&c);
  char *addr_client = inet_ntoa(_client.sin_addr);

  if (client == -1) {
    perror("Accept failed\n");
    exit(1);
  } else {
    printf("Connected with client\n");
    printf("ip-address of client: %s:%d\n", addr_client,
           ntohs(_client.sin_port));
  }

  // client_data *arg = malloc(sizeof(client_data));
  //
  // arg->socket = client;
  //
  // pthread_create(&thr_res, NULL, get_msg, (void *)arg);
  while (1) {
    int bytes_read = read(client, buffer, sizeof(buffer) - 1);

    if (bytes_read > 0) {
      buffer[bytes_read] = '\0';
      printf("Сообщение клиента:%s", buffer);
    }
    // while ((bytes_read = recv(client, buffer, sizeof(buffer) - 1, 0)) > 0) {
    //   buffer[bytes_read] = '\0';
    //   printf("Сообщение клиента:%s", buffer);
    // }

    char msg[64] = {0};

    printf(":");
    fgets(msg, 64, stdin);

    send(client, msg, strlen(msg), 0);
  }
  // pthread_exit(&thr_res);

  close(client);
  close(sock);

  return 0;
}
