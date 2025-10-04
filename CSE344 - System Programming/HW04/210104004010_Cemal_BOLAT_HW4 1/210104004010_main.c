#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

#include "buffer.h"
#include "utils.h"
#include <stdatomic.h>

#define MAX_WORKERS 128

volatile sig_atomic_t keep_running = 1;
pthread_barrier_t barrier;

void handle_sigint(int sig) {
    (void)sig;
    atomic_store(&keep_running, 0);
    fprintf(stderr, "\n[!] Interrupted. Cleaning up...\n");
}

void* manager_thread(void* arg) {
    ManagerArgs* args = (ManagerArgs*)arg;

    int fd = args->fd;
    
    SharedBuffer* buf = args->buffer;
    char *line = malloc(MAX_LINE_LEN);
    if (!line) {
        perror("Failed to allocate memory for line");
        return NULL;
    }

    while (atomic_load(&keep_running) && my_readline(fd, line, MAX_LINE_LEN) > 0) {
        buffer_add(buf, line);
    }

    // EOF marker: set flag and wake all
    pthread_mutex_lock(&buf->mutex);
    buf->eof = 1;
    pthread_cond_broadcast(&buf->not_empty);
    pthread_mutex_unlock(&buf->mutex);

    free(line);
    return NULL;
}

void* worker_thread(void* arg) {
    WorkerArgs* args = (WorkerArgs*)arg;
    SharedBuffer* buf = args->buffer;

    while (atomic_load(&keep_running)) {
        char* line = buffer_get(buf);
        if (!line) break;

        if (strstr(line, args->keyword)) {
            args->match_count++;
        }

        free(line);
    }

    printf("Worker #%d: found %d matches\n", args->id, args->match_count);

    pthread_barrier_wait(&barrier);  // Sync all workers
    return NULL;
}

void print_usage(const char* prog) {
    fprintf(stderr, "Usage: %s <buffer_size> <num_workers> <log_file> <search_term>\n", prog);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    int buffer_size = my_atoi(argv[1]);
    const char* log_file = argv[3];
    const char* keyword = argv[4];
    ManagerArgs manager_args;
    WorkerArgs* worker_args;
    pthread_t* workers;
    pthread_t manager;
    int num_workers;

    if (errno == EINVAL) {
        fprintf(stderr, "Invalid buffer size: %s\n", argv[1]);
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }
    num_workers = my_atoi(argv[2]);
    if (errno == EINVAL) {
        fprintf(stderr, "Invalid number of workers: %s\n", argv[2]);
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    int fd = open(log_file, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    signal(SIGINT, handle_sigint);

    SharedBuffer buffer;
    buffer_init(&buffer, buffer_size);

    manager_args.buffer = &buffer;
    manager_args.fd = fd;

    pthread_barrier_init(&barrier, NULL, num_workers);

    // Worker setup
    workers = malloc(sizeof(pthread_t) * num_workers);
    worker_args = malloc(sizeof(WorkerArgs) * num_workers);

    for (int i = 0; i < num_workers; ++i) {
        worker_args[i].id = i;
        worker_args[i].buffer = &buffer;
        worker_args[i].keyword = keyword;
        worker_args[i].match_count = 0;
        pthread_create(&workers[i], NULL, worker_thread, &worker_args[i]);
    }

    pthread_create(&manager, NULL, manager_thread, &manager_args);

    pthread_join(manager, NULL);
    for (int i = 0; i < num_workers; ++i)
        pthread_join(workers[i], NULL);

    int total = 0;
    for (int i = 0; i < num_workers; ++i)
        total += worker_args[i].match_count;

    printf("Total matches: %d\n", total);

    buffer_destroy(&buffer);
    pthread_barrier_destroy(&barrier);
    free(workers);
    free(worker_args);
    if (close(fd) < 0) {
        perror("Error closing file");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
