#pragma once

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define MAX_CLIENTS 100
#define USERNAME_LEN 16
#define ROOM_LEN 32
#define MAX_ROOM_USERS 32
#define MAX_QUEUE_SIZE 5
#define MAX_FILE_NAME_LEN 256
#define MAX_FILE_SIZE 3 * 1024 * 1024 // 3 MB
#define BUFFER_SIZE 1024

#define LOG_FILE "server.log"

typedef struct client_node {
    int socket_fd;
    char username[USERNAME_LEN + 1];
    char room[ROOM_LEN + 1];
    char old_rooms[MAX_ROOM_USERS][ROOM_LEN + 1];
    int old_rooms_count;
    pthread_t thread;
    struct client_node *next;
} client_node_t;

typedef struct {
    char filename[MAX_FILE_NAME_LEN];
    char *file_data;
    size_t file_size;
    char sender_username[USERNAME_LEN + 1];
    char receiver_username[USERNAME_LEN + 1];
    int sender_fd;
    time_t queue_time;
} file_transfer_t;

typedef struct {
    file_transfer_t items[MAX_QUEUE_SIZE];
    int size;
    int front;
    int rear;
    pthread_mutex_t mutex;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} file_queue_t;

typedef struct thread_list {
    pthread_t threads[MAX_CLIENTS];
    int count;
} thread_list_t;


extern thread_list_t client_threads;
extern client_node_t *client_list;
extern pthread_mutex_t client_list_mutex;
extern int server_fd;
extern pthread_mutex_t log_file_mutex;
extern int log_file_fd;
extern file_queue_t file_queue;
extern pthread_t file_worker_thread;
extern sig_atomic_t running;
extern pthread_mutex_t stdout_mutex;

extern int* whiles_fd; // Array of file descriptors for while loops
