#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  struct sockaddr_in addr;
  int sock;
  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock == -1) {
    perror("Error init socket\n");
  } else {
    printf("Socket init succses\n");
  }

  addr.sin_family = AF_INET;
  // addr.sin_addr.s_addr = INADDR_ANY;
  addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr.sin_port = htons(8000);
  
  printf("Connecting...\n");

  if (connect(sock, (const struct sockaddr *)&addr, sizeof(addr)) == -1) {
    perror("Failed connection\n");
  } else {
    printf("connected\n");
    // close(sock);
  }
  close(sock);
  return 1;
}
