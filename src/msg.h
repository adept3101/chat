#ifndef MSG_H
#define MSG_H
#define BUFF_SIZE 256
#include <time.h>
#include <pthread.h>

extern pthread_mutex_t m;
// static pthread_mutex_t m;

void* get_msg(void *arg);
void* send_msg(void *arg);
void log_msg(const char *buff, char *file); //const потому что char[] эквивалентен *char

typedef struct {
  int sock;
  char name[32];
} thread_data;


// typedef struct {
//   char buff[128];
// } log_data;

#endif // MSG_H
