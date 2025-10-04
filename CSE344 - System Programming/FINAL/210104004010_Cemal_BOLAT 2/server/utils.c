#include "utils.h"
#include "list.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <ctype.h>
#include <stdatomic.h>
#include <stdarg.h>

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
        fprintf(stderr, "Invalid port number: %s\n", port);
        exit(EXIT_FAILURE);
    }
    if (port_num <= 0 || port_num > 65535) {
        fprintf(stderr, "Invalid port number. Must be between 1 and 65535.\n");
        exit(EXIT_FAILURE);
    }
    return port_num;
}

int reconfigure_server(int port){
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0){
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, MAX_CLIENTS) < 0){
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
    return server_fd;
}

void trim_the_newline(char *str) {
    int len = (int)strlen(str);
    int i = 0;

    while (i < len && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i++;
    }

    if (i > 0) {
        memmove(str, str + i, len - i + 1);
        len -= i;
    }

    i = len - 1;
    while (i >= 0 && (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r')) {
        i--;
    }

    str[i + 1] = '\0';
}

void log_to_file(const char *msg) {

    if (msg == NULL || strlen(msg) == 0) {
        return;
    }

    if (log_file_fd < 0) {
        fprintf(stderr, "Log file not initialized.\n");
        return;
    }

    if (pthread_mutex_lock(&log_file_mutex) != 0) {
        perror("pthread_mutex_lock");
        return;
    }
    
    char time_str[32];
    time_t now = time(NULL);
    struct tm tm_info;

    localtime_r(&now, &tm_info);

    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &tm_info);


    if (write(log_file_fd, time_str, strlen(time_str)) < 0) {
        perror("write to log file");
        pthread_mutex_unlock(&log_file_mutex);
        return;
    }

    if (write(log_file_fd, " - ", 3) < 0) {
        perror("write to log file");
        pthread_mutex_unlock(&log_file_mutex);
        return;
    }

    if (write(log_file_fd, msg, strlen(msg)) < 0) {
        perror("write to log file");
    }

    if (pthread_mutex_unlock(&log_file_mutex) != 0) {
        perror("pthread_mutex_unlock");
    }
}

void init_log_file(const char *filename) {
    log_file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_file_fd < 0) {
        perror("open log file");
        exit(EXIT_FAILURE);
    }
}

int is_username_taken(const char *username) {
    pthread_mutex_lock(&client_list_mutex);
    client_node_t *curr = client_list;
    while (curr) {
        if (strcmp(curr->username, username) == 0) {
            pthread_mutex_unlock(&client_list_mutex);
            return 1; // already exists
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&client_list_mutex);
    return 0; // not found
}

void cleanup_resources(void)
{
    atomic_store(&running, 0);

    if (server_fd >= 0)
    {
        close(server_fd);
        server_fd = -1;
    }

    pthread_mutex_lock(&client_list_mutex);
    client_node_t *curr = client_list;
    while (curr)
    {
        if (curr->socket_fd >= 0)
        {
            shutdown(curr->socket_fd, SHUT_RDWR);
            close(curr->socket_fd);
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&client_list_mutex);

    pthread_mutex_lock(&file_queue.mutex);
    pthread_cond_broadcast(&file_queue.not_empty);
    pthread_cond_broadcast(&file_queue.not_full);
    pthread_mutex_unlock(&file_queue.mutex);

    if (file_worker_thread)
    {
        pthread_join(file_worker_thread, NULL);
    }

    if (whiles_fd)
    {
        free(whiles_fd);
        whiles_fd = NULL;
    }


    free_list_with_message();

    if (log_file_fd >= 0)
    {
        close(log_file_fd);
        log_file_fd = -1;
    }

    int ret;
    ret = pthread_mutex_trylock(&file_queue.mutex);
    if (ret == 0)
        pthread_mutex_unlock(&file_queue.mutex);
    pthread_mutex_destroy(&file_queue.mutex);

    ret = pthread_mutex_trylock(&client_list_mutex);
    if (ret == 0)
        pthread_mutex_unlock(&client_list_mutex);
    pthread_mutex_destroy(&client_list_mutex);

    ret = pthread_mutex_trylock(&log_file_mutex);
    if (ret == 0)
        pthread_mutex_unlock(&log_file_mutex);
    pthread_mutex_destroy(&log_file_mutex);
}

void init_username(char *usr, int client_fd) {
    ssize_t len;

    while (1) {
        len = recv(client_fd, usr, sizeof(usr) - 1, 0);
        if (len <= 0) {
            close(client_fd);
            return ;
        }

        usr[len] = '\0'; // Null-terminate the string
        trim_the_newline(usr);

        int valid = 1;
        if (strlen(usr) == 0 || strlen(usr) > USERNAME_LEN) {
            valid = 0;
        }
        for (size_t i = 0; i < strlen(usr); i++) {
            if (!isalnum(usr[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            send(client_fd, "[ERROR] Invalid username. Use alphanumeric chars, max 16.\n", 60, 0);
            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg), "[REJECTED] Invalid username attempted: %s\n", usr);
            log_to_file(log_msg);
        }
        else if (is_username_taken(usr)) {
            if (errno == SIGPIPE) {
                close(client_fd);
                return; // Client disconnected
            }
            send(client_fd, "[ERROR] Username already taken. Please choose another.\n", 56, 0);
            char log_msg[BUFFER_SIZE];
            snprintf(log_msg, sizeof(log_msg), "[REJECTED] Duplicate username attempted: %s\n", usr);
            log_to_file(log_msg);
        } else {
            const char *welcome_msg = "OK\n";
            send(client_fd, welcome_msg, strlen(welcome_msg), 0);
            break; // Valid username, exit loop
        }
    }

}


void print_proper_server_prompt(const char *username, char *buffer) {
    if (buffer == NULL || strlen(buffer) == 0) {
        return; // No message to print
    }

    trim_the_newline(buffer);
    // Check if message is a command (starts with "CMD:")
    if (strncmp(buffer, "CMD:", 4) == 0) {
        char cmd_type[32] = {0};
        char target[32] = {0};
        char message[256] = {0};

        // Parse the command format: CMD:TYPE:TARGET:MESSAGE
        sscanf(buffer + 4, "%31[^:]:%31[^:]:%255[^\n]", cmd_type, target, message);

        if (strcmp(cmd_type, "WHISPER") == 0) {
            safe_printf("[COMMAND] %s sent whisper to %s\n", username, target);
        } else if (strcmp(cmd_type, "BROADCAST") == 0) {
            safe_printf("[COMMAND] %s broadcasted to room '%s'\n", username, target);
        } else if (strcmp(cmd_type, "LEAVE") == 0) {
            safe_printf("[COMMAND] %s left room.\n", username);
        } else if (strcmp(cmd_type, "JOIN") == 0) {
            safe_printf("[COMMAND] %s joined room '%s'\n", username, target);
        } else if (strcmp(cmd_type, "EXIT") == 0) {
            safe_printf("[DISCONNECT] Client %s disconnected.\n", username);
        } else if (strcmp(cmd_type, "SENDFILE") == 0) {
            safe_printf("[COMMAND] %s sent file to %s\n", username, target);
        } else {
            safe_printf("[COMMAND] %s sent unknown command: %s\n", username, buffer);
        }
    } else {
        // Regular message, not a command
        safe_printf("[%s] %s\n", username, buffer);
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
