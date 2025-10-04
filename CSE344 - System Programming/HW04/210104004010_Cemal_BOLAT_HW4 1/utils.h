// utils.h
#ifndef UTILS_H
#define UTILS_H

#include <pthread.h>
#include <stdlib.h>
#include "buffer.h"

typedef struct {
    int id;
    SharedBuffer* buffer;
    const char* keyword;
    int match_count;
} WorkerArgs;

typedef struct {
    int fd;
    SharedBuffer* buffer;
} ManagerArgs;


int my_atoi(const char* str);
int my_readline(int fd, char* buf, size_t size);

#endif
