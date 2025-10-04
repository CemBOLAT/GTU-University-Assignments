#pragma once


#include <pthread.h>
#include <signal.h>
#include <stdatomic.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 100
#define USERNAME_LEN 16
#define min(a, b) ((a) < (b) ? (a) : (b))

#define MAX_FILE_SIZE (3 * 1024 * 1024) // 3MB

extern atomic_int sockfd;
extern pthread_mutex_t sockfd_mutex;  // Yeni mutex ekleyin
extern pthread_t *recv_thread_ptr; // Pointer to the receive thread
extern pthread_t *io_read_thread_ptr; // Pointer to the input/output read thread
extern volatile sig_atomic_t running; // Volatile to ensure proper synchronization across threads
extern char username[BUFFER_SIZE / 4]; // Username of the client

extern pthread_mutex_t file_mutex; // Mutex for file transfer synchronization
extern pthread_cond_t file_cond; // Condition variable for file transfer synchronization

extern volatile int file_transfer_active; // Flag to indicate if a file transfer is active
extern volatile int expecting_file; // Flag to indicate if the client is expecting a file
extern volatile int file_fd; // File descriptor for the currently active file transfer
extern volatile long current_file_size; // Size of the current file being transferred
extern volatile long read_bytes; // Number of bytes read in the current file transfer
extern char receiving_filepath[(BUFFER_SIZE / 2) + 32]; // Path where the received file will be saved

extern volatile int waiting_for_sendfile_response; // Flag to indicate if waiting for sendfile response
extern volatile int sendfile_approved; // Flag to indicate if the sendfile request was approved
extern pthread_mutex_t sendfile_mutex; // Mutex for sendfile synchronization
extern pthread_cond_t sendfile_cond; // Condition variable for sendfile synchronization
extern int recv_thread_joined;
extern pthread_mutex_t stdout_mutex;
