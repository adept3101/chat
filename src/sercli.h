#ifndef SERCLI_H
#define SERCLI_H

#include <netinet/in.h>
void init_addr(struct sockaddr_in *addr, int port, char *ip);
int create_server(int port, char *ip);
int connect_server(int port, char *ip);

#endif // !SERCLI_H
