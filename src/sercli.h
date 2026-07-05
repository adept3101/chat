#ifndef SERCLI_H
#define SERCLI_H

// void conn_opt();
#include <netinet/in.h>
void init_addr(struct sockaddr_in *addr, int port, char *ip);
int create_server(int port, char *ip);
void connect_server(int port, char *ip);

#endif // !SERCLI_H
