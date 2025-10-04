// buffer.c
#include "buffer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void buffer_init(SharedBuffer* buf, int capacity) {
    buf->lines = malloc(sizeof(char*) * capacity);
    buf->capacity = capacity;
    buf->count = 0;
    buf->front = 0;
    buf->rear = 0;
    buf->eof = 0;
    pthread_mutex_init(&buf->mutex, NULL);
    pthread_cond_init(&buf->not_empty, NULL);
    pthread_cond_init(&buf->not_full, NULL);
}

void buffer_destroy(SharedBuffer* buf) {
    for (int i = 0; i < buf->count; ++i) {
        int index = (buf->front + i) % buf->capacity;
        free(buf->lines[index]); // satırların belleğini boşalt
    }
    free(buf->lines);
    pthread_mutex_destroy(&buf->mutex);
    pthread_cond_destroy(&buf->not_empty);
    pthread_cond_destroy(&buf->not_full);
}

void buffer_add(SharedBuffer* buf, const char* line) {
    pthread_mutex_lock(&buf->mutex);
    while (buf->count == buf->capacity)
        pthread_cond_wait(&buf->not_full, &buf->mutex);

    buf->lines[buf->rear] = strdup(line);
    buf->rear = (buf->rear + 1) % buf->capacity;
    buf->count++;
    pthread_cond_signal(&buf->not_empty);
    pthread_mutex_unlock(&buf->mutex);
}

char* buffer_get(SharedBuffer* buf) {
    pthread_mutex_lock(&buf->mutex);
    while (buf->count == 0 && !buf->eof)
        pthread_cond_wait(&buf->not_empty, &buf->mutex);

    if (buf->count == 0 && buf->eof) {
        pthread_mutex_unlock(&buf->mutex);
        return NULL;
    }

    char* line = buf->lines[buf->front];
    buf->front = (buf->front + 1) % buf->capacity;
    buf->count--;
    pthread_cond_signal(&buf->not_full);
    pthread_mutex_unlock(&buf->mutex);
    return line;
}
