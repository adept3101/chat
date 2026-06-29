#ifndef MSG_H
#define MSG_H
#include <time.h>

void* get_msg(void *arg);
void* send_msg(void *arg);
void log_msg(const char buff[32]); //const потому что char[] эквивалентен *char

typedef struct {
  int sock;
  char name[32];
} thread_data;

typedef struct {
  char buff[128];
} log_data;

#endif // MSG_H
