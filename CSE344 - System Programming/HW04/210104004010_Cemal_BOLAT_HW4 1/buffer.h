// buffer.h
#ifndef BUFFER_H
#define BUFFER_H

#include <pthread.h>

#define MAX_LINE_LEN 1024

typedef struct {
    char** lines;
    int capacity;
    int count;
    int front;
    int rear;

    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    int eof;
} SharedBuffer;

void buffer_init(SharedBuffer* buf, int capacity);
void buffer_destroy(SharedBuffer* buf);
void buffer_add(SharedBuffer* buf, const char* line);
char* buffer_get(SharedBuffer* buf);

#endif
