#include "list.h"
#include "utils.h"
#include "server.h"
#include "commands.h"
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

// Modified handle_file_transfer function to work with new client protocol
void handle_file_transfer(client_node_t *client, const char *msg) {
    char target[USERNAME_LEN + 1], filename[MAX_FILE_NAME_LEN];
    long filesize;

    // Parse the message
    if (sscanf(msg, "CMD:SENDFILE:%16[^:]:%1023[^:]:%ld",
               target, filename, &filesize) != 3) {
        send(client->socket_fd, "[ERROR] Invalid file transfer format\n", 37, 0);
        return;
    }

    // Validate filename (only works on current directory)
    if (strstr(filename, "..") || strchr(filename, '/') || strchr(filename, '\\')) {
        send(client->socket_fd, "[ERROR] Invalid filename format\n", 32, 0);
        return;
    }

    pthread_mutex_lock(&client_list_mutex);
    // Check if target user exists
    client_node_t *target_client = find_client_by_username(target);
    pthread_mutex_unlock(&client_list_mutex);

    if (!target_client) {
        send(client->socket_fd, "[ERROR] Target user not found\n", 30, 0);
        return;
    }

    // Check if sender is trying to send to themselves
    if (strcmp(client->username, target) == 0) {
        send(client->socket_fd, "[ERROR] You cannot send a file to yourself\n", 43, 0);
        return;
    }

    // File size validation
    if (filesize <= 0) {
        send(client->socket_fd, "[ERROR] Invalid file size: must be greater than 0\n", 50, 0);
        return;
    }

    if (filesize > MAX_FILE_SIZE) {
        char error_msg[BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg),
                "[ERROR] File too large: %ld bytes (max: %d bytes)\n",
                filesize, MAX_FILE_SIZE);
        send(client->socket_fd, error_msg, strlen(error_msg), 0);
        return;
    }

    // Check file queue capacity
    pthread_mutex_lock(&file_queue.mutex);
    int current_queue_size = file_queue.size;
    pthread_mutex_unlock(&file_queue.mutex);

    if (current_queue_size >= MAX_QUEUE_SIZE) {
        char error_msg[BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg),
                "[ERROR] File transfer queue is full (%d/%d). Please try again later\n",
                current_queue_size, MAX_QUEUE_SIZE);
        send(client->socket_fd, error_msg, strlen(error_msg), 0);
        return;
    }

    // All validations passed - send OK signal to client
    if (send(client->socket_fd, "SENDFILE_OK", 11, 0) < 0) {
        perror("Failed to send SENDFILE_OK");
        return;
    }

    // Log the approval
    char log_msg[BUFFER_SIZE];
    snprintf(log_msg, sizeof(log_msg),
            "[FILE-APPROVED] File transfer '%s' from %s to %s (%ld bytes) approved\n",
            filename, client->username, target, filesize);
    log_to_file(log_msg);

    safe_printf("[FILE-TRANSFER] Approved: %s -> %s ('%s', %ld bytes)\n",
           client->username, target, filename, filesize);

    // Allocate memory for file data
    char *file_data = malloc(filesize);
    if (!file_data) {
        char error_msg[] = "[ERROR] Server memory allocation failed\n";
        send(client->socket_fd, error_msg, strlen(error_msg), 0);

        snprintf(log_msg, sizeof(log_msg),
                "[FILE-ERROR] Memory allocation failed for file '%s' (%ld bytes)\n",
                filename, filesize);
        log_to_file(log_msg);
        return;
    }

    // Receive file data with progress tracking
    long bytes_received = 0;
    time_t start_time = time(NULL);

    while (bytes_received < filesize) {
        ssize_t n = recv(client->socket_fd,
                        file_data + bytes_received,
                        filesize - bytes_received,
                        0);

        if (n <= 0) {
            free(file_data);

            // Send error back to client
            char error_msg[BUFFER_SIZE];
            snprintf(error_msg, sizeof(error_msg),
                    "[ERROR] File transfer interrupted after %ld/%ld bytes\n",
                    bytes_received, filesize);
            send(client->socket_fd, error_msg, strlen(error_msg), 0);

            // Log the failure
            snprintf(log_msg, sizeof(log_msg),
                    "[FILE-ERROR] Transfer interrupted: '%s' from %s to %s (%ld/%ld bytes)\n",
                    filename, client->username, target, bytes_received, filesize);
            log_to_file(log_msg);

            safe_printf("[FILE-ERROR] Transfer failed: %s -> %s ('%s', %ld/%ld bytes)\n",
                   client->username, target, filename, bytes_received, filesize);
            return;
        }

        bytes_received += n;

        // Optional: Print progress for large files
        if (filesize > 1024*1024) { // For files > 1MB
            time_t current_time = time(NULL);
            if (current_time - start_time >= 1) { // Every second
                safe_printf("[FILE-PROGRESS] %s -> %s: %ld/%ld bytes (%.1f%%)\n",
                       client->username, target, bytes_received, filesize,
                       (double)bytes_received * 100.0 / filesize);
                start_time = current_time;
            }
        }
    }

    // Verify we received exactly the expected amount
    if (bytes_received != filesize) {
        free(file_data);
        char error_msg[BUFFER_SIZE];
        snprintf(error_msg, sizeof(error_msg),
                "[ERROR] File size mismatch: received %ld bytes, expected %ld bytes\n",
                bytes_received, filesize);
        send(client->socket_fd, error_msg, strlen(error_msg), 0);

        snprintf(log_msg, sizeof(log_msg),
                "[FILE-ERROR] Size mismatch: '%s' from %s to %s (got %ld, expected %ld)\n",
                filename, client->username, target, bytes_received, filesize);
        log_to_file(log_msg);
        return;
    }

    // Prepare file transfer info for queue
    file_transfer_t new_file;
    memset(&new_file, 0, sizeof(file_transfer_t));

    strncpy(new_file.filename, filename, MAX_FILE_NAME_LEN - 1);
    new_file.filename[MAX_FILE_NAME_LEN - 1] = '\0';

    strncpy(new_file.receiver_username, target, USERNAME_LEN);
    new_file.receiver_username[USERNAME_LEN] = '\0';

    strncpy(new_file.sender_username, client->username, USERNAME_LEN);
    new_file.sender_username[USERNAME_LEN] = '\0';

    new_file.file_data = file_data;
    new_file.file_size = filesize;
    new_file.sender_fd = client->socket_fd;
    new_file.queue_time = time(NULL);

    // Add to queue
    pthread_mutex_lock(&file_queue.mutex);

    // Double-check queue capacity (defensive programming)
    if (file_queue.size >= MAX_QUEUE_SIZE) {
        pthread_mutex_unlock(&file_queue.mutex);
        free(file_data);
        send(client->socket_fd, "[ERROR] Queue became full during transfer\n", 42, 0);
        return;
    }

    // Add to queue
    file_queue.rear = (file_queue.rear + 1) % MAX_QUEUE_SIZE;
    file_queue.items[file_queue.rear] = new_file;
    file_queue.size++;

    current_queue_size = file_queue.size;

    // Signal worker thread
    pthread_cond_signal(&file_queue.not_empty);
    pthread_mutex_unlock(&file_queue.mutex);

    // Log successful queueing
    snprintf(log_msg, sizeof(log_msg),
            "[FILE-QUEUED] File '%s' from %s to %s queued successfully. Queue: %d/%d\n",
            filename, client->username, target, current_queue_size, MAX_QUEUE_SIZE);
    log_to_file(log_msg);

    // Send confirmation to sender
    char response[BUFFER_SIZE];
    if (current_queue_size > 1) {
        snprintf(response, sizeof(response),
                "[SUCCESS] File received and queued. Position: %d/%d\n",
                current_queue_size, MAX_QUEUE_SIZE);
    } else {
        snprintf(response, sizeof(response),
                "[SUCCESS] File received and being sent to %s\n", target);
    }
    send(client->socket_fd, response, strlen(response), 0);

    safe_printf("[FILE-RECEIVED] %s uploaded '%s' for %s (%ld bytes) - Queue: %d/%d\n",
           client->username, filename, target, filesize, current_queue_size, MAX_QUEUE_SIZE);
}

void handle_client_command(client_node_t *client, const char *msg) {
    if (strncmp(msg, "CMD:JOIN:", 9) == 0) {
        const char *room = msg + 9;
        if (strlen(room) == 0 || strlen(room) > 31) {
            send(client->socket_fd, "[ERROR] Invalid room name. Use alphanumeric chars, max 31.\n", 60, 0);
            return;
        }
        cmd_join(client, room);
        char log_msg[BUFFER_SIZE];
        // [JOIN] user 'john45' joined room 'team1
        snprintf(log_msg, sizeof(log_msg), "[JOIN] user '%s' joined room '%s'\n", client->username, client->room);
        log_to_file(log_msg);

    } else if (strncmp(msg, "CMD:LEAVE", 9) == 0) {
        cmd_leave(client);

    } else if (strncmp(msg, "CMD:BROADCAST:", 14) == 0) {
        const char *message = msg + 14;
        if (strlen(client->room) == 0) {
            send(client->socket_fd, "[ERROR] Join a room first.\n", 28, 0);
            return;
        }
        if (strlen(message) == 0) {
            send(client->socket_fd, "[ERROR] Broadcast message cannot be empty.\n", 43, 0);
            return;
        }
        cmd_broadcast(client, message);
    } else if (strncmp(msg, "CMD:WHISPER:", 12) == 0) {
        char target[USERNAME_LEN + 1], content[BUFFER_SIZE];
        const char *ptr = msg + 12;
        const char *sep = strchr(ptr, ':');
        if (!sep) {
            send(client->socket_fd, "[ERROR] Invalid whisper format.\n", 32, 0);
            return;
        }

        size_t name_len = sep - ptr;
        if (name_len > USERNAME_LEN) name_len = USERNAME_LEN;
        strncpy(target, ptr, name_len);
        target[name_len] = '\0';
        strncpy(content, sep + 1, BUFFER_SIZE - 1);
        content[BUFFER_SIZE - 1] = '\0';

        cmd_whisper(client, target, content);

    } else if (strncmp(msg, "CMD:EXIT", 8) == 0) {
        cmd_exit(client);
    } else if (strncmp(msg, "CMD:SENDFILE:", 13) == 0) {
        // Handle file transfer with enhanced logging
        char log_msg[BUFFER_SIZE];
        snprintf(log_msg, sizeof(log_msg),
                "[FILE-REQUEST] %s initiated file transfer: %s\n",
                client->username, msg + 13);
        log_to_file(log_msg);

        handle_file_transfer(client, msg);
    }
    else {
        send(client->socket_fd, "[ERROR] Unknown command\n", 24, 0);

        char log_msg[BUFFER_SIZE];
        snprintf(log_msg, sizeof(log_msg),
                "[UNKNOWN-CMD] %s sent unknown command: %.100s\n",
                client->username, msg);
        log_to_file(log_msg);
    }
}
