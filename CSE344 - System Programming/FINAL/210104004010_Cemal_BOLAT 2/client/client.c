#include "utils.h"
#include "commands.h"
#include "globals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

atomic_int sockfd = -1;
pthread_t *recv_thread_ptr = NULL;
pthread_t *io_read_thread_ptr = NULL;
volatile sig_atomic_t running = 1;
char username[BUFFER_SIZE / 4] = {0};
pthread_mutex_t stdout_mutex = PTHREAD_MUTEX_INITIALIZER;

// File transfer variables
pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t file_cond = PTHREAD_COND_INITIALIZER;

volatile int file_transfer_active = 0;
volatile int expecting_file = 0;
volatile int file_fd = -1;
volatile long current_file_size = 0;
volatile long read_bytes = 0;
char receiving_filepath[(BUFFER_SIZE / 2) + 32];

// Global variables for file sending state
volatile int waiting_for_sendfile_response = 0;
volatile int sendfile_approved = 0;
pthread_mutex_t sendfile_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sendfile_cond = PTHREAD_COND_INITIALIZER;
int recv_thread_joined = 0; //

// Function to set up file transfer (called from receive_handler)
int setup_file_transfer(const char *buffer) {
    char target[USERNAME_LEN + 1], filename[BUFFER_SIZE / 2];
    long file_size;

    char color_buffer[BUFFER_SIZE];

    if (sscanf(buffer, "CMD:SENDFILE:%16[^:]:%1023[^:]:%ld", target, filename, &file_size) != 3) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] Invalid file transfer format.\n" RESET_COLOR);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        write(STDOUT_FILENO, "> ", 2);
        return -1;
    }

    // Target check
    if (strcmp(target, username) != 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] File transfer is not for you: %s\n" RESET_COLOR, target);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        write(STDOUT_FILENO, "> ", 2);
        return -1;
    }

    // File size check
    if (file_size <= 0 || file_size > MAX_FILE_SIZE) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] Invalid file size: %ld bytes (must be > 0 and <= %d bytes)\n" RESET_COLOR, file_size, MAX_FILE_SIZE);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        write(STDOUT_FILENO, "> ", 2);
        return -1;
    }

    // Create directory
    if (mkdir("received_files", 0755) && errno != EEXIST) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] Could not create directory 'received_files': %s\n" RESET_COLOR, strerror(errno));
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return -1;
    }

    // Create filename and open file
    int fd = -1;
    snprintf(receiving_filepath, sizeof(receiving_filepath), "received_files/%s", filename);
    fd = open(receiving_filepath, O_WRONLY | O_CREAT | O_EXCL, 0644);

    if (fd < 0) {
        if (errno == EEXIST) {
            // If file exists, add number suffix
            char info_msg[BUFFER_SIZE];
            snprintf(info_msg, sizeof(info_msg), YELLOW_COLOR "\r[INFO] File already exists: '%s'. Adding number suffix.\n", filename);
            write(STDOUT_FILENO, info_msg, strlen(info_msg));

            int i = 1;
            while (i < 100) {
                snprintf(receiving_filepath, sizeof(receiving_filepath), "received_files/%s_%d", filename, i);
                fd = open(receiving_filepath, O_WRONLY | O_CREAT | O_EXCL, 0644);
                if (fd >= 0) break;
                i++;
            }
            if (fd < 0) {
                snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] Could not create file '%s': %s\n" RESET_COLOR, receiving_filepath, strerror(errno));
                write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                return -1;
            }
        } else {
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] Could not open file '%s': %s\n" RESET_COLOR, receiving_filepath, strerror(errno));
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            return -1;
        }
    }

    // Clean up previous transfer if active
    if (file_transfer_active && file_fd >= 0) {
        close(file_fd);
    }

    // Start new transfer
    file_fd = fd;
    current_file_size = file_size;
    read_bytes = 0;
    file_transfer_active = 1;
    expecting_file = 1;

    snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "\r[INFO] File transfer initiated: '%s' (%ld bytes)\n" RESET_COLOR, filename, file_size);
    write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
    write(STDOUT_FILENO, "> ", 2);

    return 0;
}

void *receive_handler(void *arg) {
    char buffer[BUFFER_SIZE / 2];
    char color_buffer[BUFFER_SIZE];
    (void)arg;

    int local_sockfd;

    while (atomic_load(&running)) {
        local_sockfd = atomic_load(&sockfd);
        if (local_sockfd < 0) {
            safe_printf(YELLOW_COLOR "\r[ERROR] Socket is not connected.\n" RESET_COLOR);
            atomic_store(&running, 0);
            return NULL;
        }
        ssize_t len = recv(local_sockfd, buffer, sizeof(buffer) - 1, 0);
        if (len <= 0) {
            safe_printf(YELLOW_COLOR "\r[SERVER DISCONNECTED].\n" RESET_COLOR);
            atomic_store(&running, 0);
            return NULL;
        }
        buffer[len] = '\0';

        // Check for file sending response
        pthread_mutex_lock(&sendfile_mutex);
        if (waiting_for_sendfile_response) {
            if (strncmp(buffer, "SENDFILE_OK", 11) == 0) {
                sendfile_approved = 1;
                waiting_for_sendfile_response = 0;
                pthread_cond_signal(&sendfile_cond);
                pthread_mutex_unlock(&sendfile_mutex);
                continue; // Don't print this message
            } else if (strncmp(buffer, "[ERROR]", 7) == 0 || strncmp(buffer, "[SUCCESS]", 9) == 0) {
                // Server rejected or responded with error/success message
                sendfile_approved = 0;
                waiting_for_sendfile_response = 0;
                pthread_cond_signal(&sendfile_cond);
                pthread_mutex_unlock(&sendfile_mutex);
                // Print the server response and continue
                write(STDOUT_FILENO, "\r", 1);
                if (strncmp(buffer, "[ERROR]", 7) == 0) {
                    snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "%s" RESET_COLOR, buffer);
                } else {
                    snprintf(color_buffer, sizeof(color_buffer), GREEN_COLOR "%s" RESET_COLOR, buffer);
                }
                write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                write(STDOUT_FILENO, "> ", 2);
                continue;
            }
        }
        pthread_mutex_unlock(&sendfile_mutex);

        // Check for file transfer command first
        if (strncmp(buffer, "CMD:SENDFILE", 12) == 0) {
            pthread_mutex_lock(&file_mutex);
            setup_file_transfer(buffer);
            pthread_mutex_unlock(&file_mutex);
            continue;
        }

        // Handle file data if in transfer mode
        pthread_mutex_lock(&file_mutex);
        if (file_transfer_active && expecting_file) {
            // Write file data
            long current_bytes = 0;
            while (current_bytes < len) {
                ssize_t written = write(file_fd, buffer + current_bytes, len - current_bytes);
                if (written < 0) {
                    if (errno == EINTR) continue;
                    snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] Failed to write to file '%s': %s\n" RESET_COLOR, receiving_filepath, strerror(errno));
                    write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                    close(file_fd);
                    file_fd = -1;
                    file_transfer_active = 0;
                    expecting_file = 0;
                    pthread_mutex_unlock(&file_mutex);
                    snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] File transfer failed: '%s'.\n" RESET_COLOR, receiving_filepath);
                    write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                    write(STDOUT_FILENO, "> ", 2);
                    break;
                }
                current_bytes += written;
            }

            // Update progress
            read_bytes += current_bytes;

            // Check if transfer completed
            if (read_bytes >= current_file_size) {
                close(file_fd);
                file_fd = -1;
                file_transfer_active = 0;
                expecting_file = 0;
                pthread_mutex_unlock(&file_mutex);
                snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "\r[INFO] File transfer completed: '%s' (%ld bytes)\n" RESET_COLOR, receiving_filepath, read_bytes);
                write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                write(STDOUT_FILENO, "> ", 2);
            } else {
                pthread_mutex_unlock(&file_mutex);
            }
            continue;
        }
        pthread_mutex_unlock(&file_mutex);

        // Handle normal messages
        if (strstr(buffer, "Disconnected")) {
            write(STDOUT_FILENO, "\r", 1);
            snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "\r%s\n" RESET_COLOR, buffer);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            atomic_store(&running, 0);
            close(atomic_load(&sockfd));
            exit(0);
        } else {
            // Normal message
            write(STDOUT_FILENO, "\r", 1);
            if (strncmp(buffer, "[ERROR]", 7) == 0) {
                snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "%s" RESET_COLOR, buffer);
            } else if (strncmp(buffer, "[SUCCESS]", 9) == 0) {
                snprintf(color_buffer, sizeof(color_buffer), GREEN_COLOR "%s" RESET_COLOR, buffer);
            } else if (strncmp(buffer, "[INFO]", 6) == 0) {
                snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "%s" RESET_COLOR, buffer);
            } else {
                snprintf(color_buffer, sizeof(color_buffer), BLUE_COLOR "%s" RESET_COLOR, buffer);
            }
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            write(STDOUT_FILENO, "> ", 2);
        }
    }
    return NULL;
}

int connect_to_server(const char *server_ip, int port) {
    struct sockaddr_in server_addr;
    char color_buffer[BUFFER_SIZE];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Could not create socket: %s\n" RESET_COLOR, strerror(errno));
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        return -1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, server_ip, &server_addr.sin_addr) <= 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Invalid address/Address not supported: %s\n" RESET_COLOR, server_ip);
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        close(sockfd);
        return -1;
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Connection failed: %s\n" RESET_COLOR, strerror(errno));
        write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        close(sockfd);
        return -1;
    }
    return 0;
}

void handle_sigint(int sig)
{
    (void)sig;


    // do broadcast exit message
    char exit_message[BUFFER_SIZE];
    snprintf(exit_message, sizeof(exit_message), "CMD:EXIT:%s", username);
    if (atomic_load(&sockfd) >= 0) {
        send(atomic_load(&sockfd), exit_message, strlen(exit_message), 0);
    }

    atomic_store(&running, 0);

    // sockfd'yi atomik olarak kapat
    int local_sockfd = atomic_load(&sockfd);
    if (local_sockfd >= 0)
    {
        shutdown(local_sockfd, SHUT_RDWR); // Bloke olan recv'i kesintiye uğrat
        close(local_sockfd);
        atomic_store(&sockfd, -1);
    }

    char color_buffer[BUFFER_SIZE];
    snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "\n[DISCONNECTED]\n" RESET_COLOR);
    write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
    cleanup_resources();
    exit(0);
}

void *input_handler(void *arg) {
    (void)arg; // Unused parameter
    char color_buffer[BUFFER_SIZE];
    while (atomic_load(&running)) {
        char input[BUFFER_SIZE / 2];
        write(STDOUT_FILENO, "> ", 2);
        int n = read(STDIN_FILENO, input, (BUFFER_SIZE / 2) - 1);
        if (n <= 0) {
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "\r[ERROR] read() failed or input closed.\n" RESET_COLOR);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            break;
        }
        input[n] = '\0';
        input[strcspn(input, "\n\r")] = '\0';

        // Skip empty input or only whitespace
        if (strlen(input) == 0 || strspn(input, " \t\n\r") == strlen(input)) {
            continue;
        }

        if (strncmp(input, "/exit", 5) == 0) {
            cmd_exit(atomic_load(&sockfd));
        }
        else if (strncmp(input, "/join ", 6) == 0) {
            char *room_name = input + 6;
            cmd_join(atomic_load(&sockfd), room_name);
        } else if (strncmp(input, "/leave", 6) == 0) {
            cmd_leave(atomic_load(&sockfd));
        } else if (strncmp(input, "/broadcast ", 11) == 0) {
            char *message = input + 11;
            cmd_broadcast(atomic_load(&sockfd), message);
        } else if (strncmp(input, "/whisper ", 9) == 0) {
            char *rest = input + 9;
            char *target = strtok(rest, " ");
            char *message = strtok(NULL, "");
            if (!target || !message) {
                snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Invalid whisper command format. Usage: /whisper <username> <message>\n" RESET_COLOR);
                write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                continue;
            }
            cmd_whisper(atomic_load(&sockfd), target, message);
        } else if (strncmp(input, "/sendfile", 9) == 0) {
            char *rest = input + 10;
            char *target = strtok(rest, " ");
            char *filename = strtok(NULL, "");
            if (!target || !filename) {
                snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Invalid sendfile command format. Usage: /sendfile <username> <filename>\n" RESET_COLOR);
                write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
                continue;
            }
            cmd_sendfile(atomic_load(&sockfd), target, filename);
        } else if (strncmp(input, "/help", 5) == 0) {
            snprintf(color_buffer, sizeof(color_buffer), YELLOW_COLOR "\r[INFO] Displaying available commands:\n" RESET_COLOR);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
            snprintf(color_buffer, sizeof(color_buffer),
                "Available commands:\n"
                "  /exit - Exit the chat client\n"
                "  /join <room_name> - Join a chat room\n"
                "  /leave - Leave the current chat room\n"
                "  /broadcast <message> - Broadcast a message to the room\n"
                "  /whisper <username> <message> - Send a private message to a user\n"
                "  /sendfile <username> <filename> - Send a file to a user\n"
                "  /help - Show this help message\n");
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        }
        else {
            snprintf(color_buffer, sizeof(color_buffer), RED_COLOR "[ERROR] Unknown command: '%s'. Try /help for available commands.\n" RESET_COLOR, input);
            write(STDOUT_FILENO, color_buffer, strlen(color_buffer));
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        safe_printf(YELLOW_COLOR "Usage: ./chatclient <server_ip> <port>\n" RESET_COLOR);
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, handle_sigint);

    const char *server_ip = argv[1];
    int port = get_port(argv[2]);

    if (connect_to_server(server_ip, port) < 0) {
        exit(EXIT_FAILURE);
    }

    enter_with_valid_username(username);

    pthread_t io_read_thread;
    io_read_thread_ptr = &io_read_thread;

    pthread_create(&io_read_thread, NULL, input_handler, NULL);

    pthread_detach(io_read_thread);

    pthread_t recv_thread;
    recv_thread_ptr = &recv_thread;
    pthread_create(&recv_thread, NULL, receive_handler, NULL);

    pthread_join(recv_thread, NULL);
    recv_thread_joined = 1;
    cleanup_resources();
    return 0;
}
