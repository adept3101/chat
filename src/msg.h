#ifndef MSG_H
#define MSG_H

char get_msg(int sock, char buff[]);
char send_msg(char *usr, int sock, char buff[]);

#endif // MSG_H
