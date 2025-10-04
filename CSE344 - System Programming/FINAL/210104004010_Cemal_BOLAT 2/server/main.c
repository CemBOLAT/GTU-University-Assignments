#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <stdatomic.h>

#include "list.h"
#include "server.h"
#include "utils.h"

int server_fd = -1;
int log_file_fd = -1;
int* whiles_fd = NULL;
pthread_mutex_t client_list_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t log_file_mutex = PTHREAD_MUTEX_INITIALIZER;
client_node_t *client_list = NULL;
sig_atomic_t running = 1;
pthread_mutex_t running_mutex = PTHREAD_MUTEX_INITIALIZER;
file_queue_t file_queue = {0};
thread_list_t client_threads = {0};
pthread_t file_worker_thread;
pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

void handle_sigint(int sig)
{
    (void)sig; // Unused parameter

    pthread_mutex_lock(&client_list_mutex);

    int client_count = len_list(client_list);

    pthread_mutex_unlock(&client_list_mutex);

    safe_printf("\n[SHUTDOWN] SIGINT received. Disconnecting %d clients and saving logs...\n", client_count);

    char shutdown_log[BUFFER_SIZE];
    snprintf(shutdown_log, sizeof(shutdown_log), "[SHUTDOWN] Server is shutting down. Disconnecting %d clients and saving logs.\n", client_count);
    log_to_file(shutdown_log);

    cleanup_resources();
    exit(0);
}

void *client_handler(void *arg) {
    int client_fd = *(int *)arg;
    free(arg);

    char username[BUFFER_SIZE] = {0};
    ssize_t len;

    signal(SIGPIPE, SIG_IGN); // Ignore broken pipe signals
    init_username(username, client_fd);


    if (strlen(username) == 0) {
        close(client_fd);
        return NULL;
    }

    char ip_str[INET_ADDRSTRLEN];

    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    if (getpeername(client_fd, (struct sockaddr *)&addr, &addr_len) < 0) {
        perror("getpeername failed");
        close(client_fd);
        return NULL;
    }
    if (inet_ntop(AF_INET, &addr.sin_addr, ip_str, sizeof(ip_str)) == NULL) {
        perror("inet_ntop failed");
        close(client_fd);
        return NULL;
    }

    safe_printf("[CONNECT] Client connected: user=%s\n", username);

    char log_msg[BUFFER_SIZE] = {0};

    char username_copy[USERNAME_LEN + 1] = {0};
    strncpy(username_copy, username, USERNAME_LEN);
    username_copy[USERNAME_LEN] = '\0';

    snprintf(log_msg, sizeof(log_msg), "[LOGIN] user '%s' connected from %s:%d\n", username_copy, ip_str, ntohs(addr.sin_port));

    log_to_file(log_msg);

    client_node_t *client = malloc(sizeof(client_node_t));
    client->socket_fd = client_fd;
    strncpy(client->username, username, USERNAME_LEN);
    client->room[0] = '\0';
    client->next = NULL;
    client->old_rooms_count = 0;
    for (int i = 0; i < MAX_ROOM_USERS; i++) {
        client->old_rooms[i][0] = '\0';
    }

    pthread_mutex_lock(&client_list_mutex);
    add_client(client);
    pthread_mutex_unlock(&client_list_mutex);

    char buffer[1024];
    int should_run = 1;
    while (should_run && (len = recv(client_fd, buffer, sizeof(buffer) - 1, 0)) > 0) {
        buffer[len] = '\0';
        print_proper_server_prompt(client->username, buffer);
        trim_the_newline(buffer);
        handle_client_command(client, buffer);

        should_run = atomic_load(&running);
    }
    // DISCONNECT] user 'mehmet1' lost connection. Cleaned up resources.

    if (atomic_load(&running) != 0) {
        safe_printf("[DISCONNECT] %s lost connection. Cleaned up resources\n", client->username);

        snprintf(log_msg, sizeof(log_msg), "[DISCONNECT] user '%s' lost connection. Cleaned up resources.\n", client->username);
        log_to_file(log_msg);

    }
    pthread_mutex_lock(&client_list_mutex);
    remove_client(client_fd);
    pthread_mutex_unlock(&client_list_mutex);
    return NULL;
}


// File transfer worker thread function
void* file_transfer_worker(void *arg) {
    (void)arg; // Unused parameter

    while (running) {
        // Wait for files in the queue
        pthread_mutex_lock(&file_queue.mutex);

        // Wait until there is at least one file in the queue
        while (file_queue.size == 0 && running) {
            pthread_cond_wait(&file_queue.not_empty, &file_queue.mutex);
        }

        if (!running) {
            pthread_mutex_unlock(&file_queue.mutex);
            break;
        }

        // Dequeue the file transfer request
        file_transfer_t current_file = file_queue.items[file_queue.front];
        file_queue.front = (file_queue.front + 1) % MAX_QUEUE_SIZE;
        file_queue.size--;

        // Signal that queue is not full anymore
        pthread_cond_signal(&file_queue.not_full);
        pthread_mutex_unlock(&file_queue.mutex);

        // Find the recipient client
        client_node_t *recipient = NULL;
        pthread_mutex_lock(&client_list_mutex);

        recipient = find_client_by_username(current_file.receiver_username);
        pthread_mutex_unlock(&client_list_mutex);

        // No recipient found
        if (!recipient) {
            char error_msg[BUFFER_SIZE];
            snprintf(error_msg, sizeof(error_msg),
                    "[ERROR] User '%s' is not connected. File not sent.\n",
                    current_file.receiver_username);
            send(current_file.sender_fd, error_msg, strlen(error_msg), 0);

            // Log kaydı
            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg),
                    "[FILE-ERROR] Failed to send file '%s' from '%s' to '%s': recipient not found\n",
                    current_file.filename, current_file.sender_username, current_file.receiver_username);
            log_to_file(log_msg);

            free(current_file.file_data);
            continue;
        }

        // Calculate wait time
        time_t wait_time = time(NULL) - current_file.queue_time;

        // First send the header
        char header[BUFFER_SIZE];
        snprintf(header, sizeof(header), "CMD:SENDFILE:%s:%s:%zu\n",
                 current_file.receiver_username, current_file.filename, current_file.file_size);

        if (send(recipient->socket_fd, header, strlen(header), 0) < 0) {
            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg),
                    "[FILE-ERROR] Failed to send header to '%s' for file '%s'\n",
                    current_file.receiver_username, current_file.filename);
            log_to_file(log_msg);

            // Gönderene bildir
            char error_msg[BUFFER_SIZE];
            snprintf(error_msg, sizeof(error_msg),
                    "[ERROR] Failed to send file '%s' to '%s'.\n",
                    current_file.filename, current_file.receiver_username);
            send(current_file.sender_fd, error_msg, strlen(error_msg), 0);

            free(current_file.file_data);
            continue;
        }

        if (send(recipient->socket_fd, current_file.file_data, current_file.file_size, 0) < 0) {
            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg),
                    "[FILE-ERROR] Failed to send data to '%s' for file '%s'\n",
                    current_file.receiver_username, current_file.filename);
            log_to_file(log_msg);

            char error_msg[BUFFER_SIZE];
            snprintf(error_msg, sizeof(error_msg),
                    "[ERROR] Failed to send file '%s' to '%s'.\n",
                    current_file.filename, current_file.receiver_username);
            send(current_file.sender_fd, error_msg, strlen(error_msg), 0);
        } else {
            char log_msg[BUFFER_SIZE];

            if (wait_time > 0) {
                snprintf(log_msg, sizeof(log_msg),
                         "[FILE] '%s' from user '%s' started upload after %ld seconds in queue.\n",
                         current_file.filename, current_file.sender_username, wait_time);
                log_to_file(log_msg);
            }

            snprintf(log_msg, sizeof(log_msg),
                    "[SEND FILE] '%s' sent from %s to %s\n",
                    current_file.filename, current_file.sender_username, current_file.receiver_username);
            log_to_file(log_msg);

            char success_msg[BUFFER_SIZE];
            snprintf(success_msg, sizeof(success_msg),
                    "[SUCCESS] File '%s' successfully sent to %s\n",
                    current_file.filename, current_file.receiver_username);
            send(current_file.sender_fd, success_msg, strlen(success_msg), 0);
        }

        free(current_file.file_data);
    }

    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./chatserver <port>\n");
        exit(EXIT_FAILURE);
    }


    client_threads.count = 0;

    init_log_file(LOG_FILE);
    if (log_file_fd < 0) {
        fprintf(stderr, "Failed to open log file.\n");
        exit(EXIT_FAILURE);
    }

    init_file_queue(&file_queue);

    pthread_create(&file_worker_thread, NULL, file_transfer_worker, NULL);

    signal(SIGINT, handle_sigint);

    int port = get_port(argv[1]);
    server_fd = -1;

    server_fd = reconfigure_server(port);

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);


    safe_printf("[INFO] Server started on port %d\n", port);

    while (1) {
        int *client_fd = malloc(sizeof(int));
        whiles_fd = client_fd;
        *client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (*client_fd < 0) {
            perror("accept");
            free(client_fd);
            continue;
        }

        pthread_t tid;
        pthread_create(&tid, NULL, client_handler, client_fd);
        client_threads.threads[client_threads.count++] = tid;
        if (client_threads.count >= MAX_CLIENTS) {
            fprintf(stderr, "[ERROR] Maximum client limit reached. Cannot accept more clients.\n");
            close(*client_fd);
            free(client_fd);
            continue;
        }
        pthread_detach(tid);
    }

    return 0;
}
