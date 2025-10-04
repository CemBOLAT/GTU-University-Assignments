#include "utils.h"
#include "globals.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include <stdarg.h>
#include <sys/stat.h>

int my_atoi(const char *str){
    int res = 0;
    int multiplier = 1;
    if (!str){
        errno = EINVAL;
        return -1;
    }
    if (str[0] == '-'){
        multiplier = -1;
        str++;
    }
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] < '0' || str[i] > '9'){
            errno = EINVAL;
            return -1;
        }
        res = res * 10 + str[i] - '0';
    }
    return res * multiplier;
}

int get_port(const char *port){
    int port_num = my_atoi(port);
    if (errno == EINVAL){
        safe_printf(RED_COLOR "[ERROR] Invalid port number: %s\n" RESET_COLOR, port);
        exit(EXIT_FAILURE);
    }
    if (port_num <= 0 || port_num > 65535) {
        safe_printf(RED_COLOR "[ERROR] Invalid port number: %d. Must be between 1 and 65535.\n" RESET_COLOR, port_num);
        exit(EXIT_FAILURE);
    }
    return port_num;
}

int reconfigure_server(int port){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0){
        safe_printf(RED_COLOR "[ERROR] Socket creation failed.\n" RESET_COLOR);
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        safe_printf(RED_COLOR "[ERROR] Setsockopt failed.\n" RESET_COLOR);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        safe_printf(RED_COLOR "[ERROR] Bind failed on port %d.\n" RESET_COLOR, port);
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0){
        safe_printf(RED_COLOR "[ERROR] Listen failed on port %d.\n" RESET_COLOR, port);
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void cleanup_resources() {
    if (!recv_thread_joined && recv_thread_ptr != NULL)
    {
        pthread_cancel(*recv_thread_ptr);
        pthread_join(*recv_thread_ptr, NULL);
        recv_thread_joined = 1;
    }

    if (atomic_load(&sockfd) >= 0) {
        close(atomic_load(&sockfd));
        atomic_store(&sockfd, -1);
    }
    pthread_mutex_lock(&file_mutex);
    if (file_transfer_active && file_fd >= 0) {
        close(file_fd);
        file_fd = -1;
    }
    pthread_mutex_unlock(&file_mutex);

    pthread_mutex_lock(&sendfile_mutex);
    if (waiting_for_sendfile_response) {
        waiting_for_sendfile_response = 0;
        sendfile_approved = 0;
    }
    pthread_mutex_unlock(&sendfile_mutex);

    pthread_mutex_destroy(&file_mutex);

    pthread_cond_destroy(&file_cond);

    pthread_mutex_destroy(&sendfile_mutex);

    pthread_cond_destroy(&sendfile_cond);

}

int file_check_while_sending(const char *filename, int fd, struct stat *file_stat) {
    char excepted_extensions[][5] = {".txt", ".pdf", ".jpg", ".png"};

    char log_msg[BUFFER_SIZE];


    if (fd < 0) {
        snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] Could not open file: %s\n" RESET_COLOR, filename);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        return -1; // File does not exist or cannot be opened
    }
    if (fstat(fd, file_stat) < 0) {
        snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] Could not get file stats: %s\n" RESET_COLOR, filename);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        close(fd);
        return -1; // Failed to get file stats
    }
    if (file_stat->st_size <= 0) {
        close(fd);
        snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] File is empty or has invalid size: %s\n" RESET_COLOR, filename);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        return -1; // Invalid file size
    }
    if (file_stat->st_size > MAX_FILE_SIZE) {
        close(fd);
        snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] File too large: %s (%ld bytes, max %d bytes)\n" RESET_COLOR, filename, file_stat->st_size, MAX_FILE_SIZE);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        return -1; // File too large
    }
    const char *ext = strrchr(filename, '.');
    if (ext == NULL) {
        close(fd);
        snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] Invalid file format: %s (no extension)\n" RESET_COLOR, filename);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        return -1; // Invalid file format
    }
    int valid_extension = 0;
    for (size_t i = 0; i < sizeof(excepted_extensions) / sizeof(excepted_extensions[0]); i++) {
        if (strcmp(ext, excepted_extensions[i]) == 0) {
            valid_extension = 1;
            break;
        }
    }
    if (!valid_extension) {
        close(fd);
        snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] Unsupported file format: %s (supported formats: .txt, .pdf, .jpg, .png)\n" RESET_COLOR, filename);
        write(STDOUT_FILENO, log_msg, strlen(log_msg));
        return -1; // Unsupported file format
    }
    return 0; // File is valid for sending
}

void enter_with_valid_username(char *username) {
    char server_reply[BUFFER_SIZE / 2];
    char color_buffer[BUFFER_SIZE];

    char *welcome_prompt= "Enter username: ";

    while (1) {
        write(STDOUT_FILENO, welcome_prompt, strlen(welcome_prompt));
        ssize_t n = read(STDIN_FILENO, username, BUFFER_SIZE - 1);
        if (n <= 0) {
            safe_printf("[ERROR] read() failed or input closed.\n");
            exit(EXIT_FAILURE);
        }
        username[n] = '\0';
        username[strcspn(username, "\n\r")] = '\0';

        int valid = 1;

        // Validate username
        if (strlen(username) == 0 || strlen(username) > USERNAME_LEN - 1) {
            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] Username must be between 1 and %d characters long.\n" RESET_COLOR, USERNAME_LEN - 1);
            write(STDOUT_FILENO, log_msg, strlen(log_msg));
            valid = 0;
            continue;
        }
        for (size_t i = 0; i < strlen(username); i++) {
            if (!isalnum(username[i])) {
                char log_msg[BUFFER_SIZE];
                snprintf(log_msg, sizeof(log_msg), RED_COLOR "[ERROR] Username '%s' contains invalid characters.\n" RESET_COLOR, username);
                write(STDOUT_FILENO, log_msg, strlen(log_msg));
                valid = 0;
                break;
            }
        }

        if (!valid) continue;

        // Send username to server
        snprintf(server_reply, sizeof(server_reply), "%s\n", username);
        if (send(atomic_load(&sockfd), server_reply, strlen(server_reply), 0) < 0) {
            close(atomic_load(&sockfd));
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Could not send username '%s' to server.\n" RESET_COLOR, username);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            exit(EXIT_FAILURE);
        }

        // Wait for server response
        ssize_t len = recv(atomic_load(&sockfd), server_reply, sizeof(server_reply) - 1, 0);
        if (len <= 0) {
            close(atomic_load(&sockfd));
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Could not receive response from server.\n" RESET_COLOR);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            exit(EXIT_FAILURE);
        }
        server_reply[len] = '\0';

        username[strcspn(username, "\n\r")] = '\0';

        if (strncmp(server_reply, "OK", 2) == 0) {
            snprintf(color_buffer, sizeof(color_buffer), GREEN_COLOR "[SUCCESS] Username '%s' is valid.\n" RESET_COLOR, username);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            break; // Valid username
        } else {
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "%s" RESET_COLOR, server_reply);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));

        }

    }
}

void safe_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    pthread_mutex_lock(&stdout_mutex);
    vprintf(format, args);
    fflush(stdout);
    pthread_mutex_unlock(&stdout_mutex);

    va_end(args);
}
