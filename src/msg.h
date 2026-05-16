#ifndef MSG_H
#define MSG_H

void* get_msg(void *arg);
void* send_msg(void *arg);

typedef struct {
  int sock;
  char name[32];
} thread_data;

#endif // MSG_H
