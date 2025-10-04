
#include "commands.h"
#include "utils.h"
#include "globals.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <sys/socket.h>

void cmd_exit(int sockfd) {
    atomic_store(&running, 0); // Set running to 0 to stop the main loop
    send(sockfd, "CMD:EXIT", strlen("CMD:EXIT"), 0);
}

void cmd_join(int sockfd, const char *room_name) {
    char color_buffer[BUFFER_SIZE];
    if (room_name == NULL || strlen(room_name) == 0) {

        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Room name required.\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return;
    } else if (strlen(room_name) > 32) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Room name cannot exceed 32 characters.\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return;
    }

    char msg[BUFFER_SIZE];
    snprintf(msg, sizeof(msg), "CMD:JOIN:%s\n", room_name);
    send(sockfd, msg, strlen(msg), 0);
}

void cmd_leave(int sockfd) {
    send(sockfd, "CMD:LEAVE", strlen("CMD:LEAVE"), 0);
}

void cmd_broadcast(int sockfd, const char *message) {
    char color_buffer[BUFFER_SIZE];
    if (message == NULL || strlen(message) == 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Usage: /broadcast <message>\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return;
    }

    char msg[BUFFER_SIZE];
    snprintf(msg, sizeof(msg), "CMD:BROADCAST:%s\n", message);
    send(sockfd, msg, strlen(msg), 0);
}

void cmd_whisper(int sockfd, const char *target, const char *message) {
    char color_buffer[BUFFER_SIZE];
    if (target == NULL || strlen(target) == 0 || message == NULL || strlen(message) == 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Usage: /whisper <username> <message>\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return;
    }

    char msg[BUFFER_SIZE];
    snprintf(msg, sizeof(msg), "CMD:WHISPER:%s:%s\n", target, message);
    send(sockfd, msg, strlen(msg), 0);
}


void cmd_sendfile(int sockfd, const char *target, const char *filename) {

    char color_buffer[BUFFER_SIZE];

    if (strcmp(target, username) == 0) {
        // Cannot send file to self
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] You cannot send a file to yourself.\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return;
    }

    int fd = open(filename, O_RDONLY);
    struct stat file_stat;
    if (file_check_while_sending(filename, fd, &file_stat) < 0) {
        return; // Problem with file check
    }

    // 1. Set up waiting state
    pthread_mutex_lock(&sendfile_mutex);
    waiting_for_sendfile_response = 1;
    sendfile_approved = 0;
    pthread_mutex_unlock(&sendfile_mutex);

    // 2. Send file request header to server
    char header[BUFFER_SIZE];
    snprintf(header, sizeof(header), "CMD:SENDFILE:%s:%s:%ld\n", target, filename, file_stat.st_size);
    if (send(sockfd, header, strlen(header), 0) < 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Failed to send file request header: %s\n" RESET_COLOR, strerror(errno));
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        close(fd);
        // Reset waiting state
        pthread_mutex_lock(&sendfile_mutex);
        waiting_for_sendfile_response = 0;
        pthread_mutex_unlock(&sendfile_mutex);
        return;
    }

    // 3. Wait for server response with timeout
    pthread_mutex_lock(&sendfile_mutex);
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec += 5; // 5 second timeout

    int wait_result = 0;
    while (waiting_for_sendfile_response && wait_result == 0) {
        wait_result = pthread_cond_timedwait(&sendfile_cond, &sendfile_mutex, &ts);
    }

    if (wait_result == ETIMEDOUT) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Server response timeout. Please try again.\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        waiting_for_sendfile_response = 0;
        pthread_mutex_unlock(&sendfile_mutex);
        close(fd);
        return;
    }

    int approved = sendfile_approved;
    pthread_mutex_unlock(&sendfile_mutex);

    // 4. If approved, send file data
    if (approved) {
        snprintf(color_buffer, sizeof(color_buffer), GREEN_COLOR "[SUCCESS] File transfer request approved. Sending file '%s' to '%s'...\n" RESET_COLOR, filename, target);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));

        char buffer[BUFFER_SIZE];
        ssize_t bytes_read;
        long total_sent = 0;

        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
            if (send(sockfd, buffer, bytes_read, 0) < 0) {
                snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Failed to send file '%s' to '%s': %s\n" RESET_COLOR, filename, target, strerror(errno));
                write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                close(fd);
                return;
            }
            total_sent += bytes_read;
        }

        if (bytes_read < 0) {
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Failed to read file '%s': %s\n" RESET_COLOR, filename, strerror(errno));
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            close(fd);
            return;
        } else {
            snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "[INFO] File '%s' sent successfully to '%s' (%ld bytes).\n" RESET_COLOR, filename, target, total_sent);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        }
    }
    close(fd);
}
