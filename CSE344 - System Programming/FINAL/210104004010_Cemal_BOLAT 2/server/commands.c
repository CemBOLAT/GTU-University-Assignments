
#include "commands.h"
#include "global.h"
#include "utils.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void broadcast(const char *msg, int sender_fd, const char *room) {
    if (room == NULL || strlen(room) == 0) {
        return; // No room specified
    }
    if (msg == NULL || strlen(msg) == 0) {
        return; // No message to broadcast
    }
    if (sender_fd < 0) {
        return; // Invalid sender socket
    }

    pthread_mutex_lock(&client_list_mutex);
    client_node_t *curr = client_list;
    while (curr) {
        if (curr->socket_fd != sender_fd) {
            if (strcmp(curr->room, room) == 0) {
                send(curr->socket_fd, msg, strlen(msg), 0);
            }
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&client_list_mutex);
}

void cmd_join(client_node_t *client, const char *room) {
    if (client == NULL || room == NULL || strlen(room) == 0) {
        return; // Invalid parameters
    }

    char old_room[32];
    strcpy(old_room, client->room);

    pthread_mutex_lock(&client_list_mutex);
    client_node_t *curr = client_list;
    int room_count = 0;
    while (curr) {
        if (strcmp(curr->room, room) == 0) {
            room_count++;
        }
        curr = curr->next;
    }
    if (room_count >= MAX_ROOM_USERS) {
        pthread_mutex_unlock(&client_list_mutex);
        send(client->socket_fd, "[ERROR] Room is full. Cannot join.\n", strlen("[ERROR] Room is full. Cannot join.\n"), 0);
        return;
    }
    strncpy(client->room, room, 31);
    pthread_mutex_unlock(&client_list_mutex);

    char response[BUFFER_SIZE];
    if (strcmp(client->room, old_room) == 0) {
        send(client->socket_fd, "[INFO] You are already in this room.\n", strlen("[INFO] You are already in this room.\n"), 0);
        return;
    }
    else if (strlen(old_room) > 0) {
        int rejoined = 0;
        if (client->old_rooms_count > 0) {
            int i = 0;
            while (i < client->old_rooms_count) {
                if (strcmp(client->old_rooms[i], client->room) == 0) {
                    rejoined = 1;
                    break;
                }
                i++;
            }
        }
        if (!rejoined) {
            snprintf(response, sizeof(response),
                 "[ROOM] %s left '%s', joined '%s'\n",
                 client->username, old_room, client->room);

            if (client->old_rooms_count < MAX_ROOM_USERS) {
                strncpy(client->old_rooms[client->old_rooms_count], client->room, sizeof(client->old_rooms[client->old_rooms_count]));
                client->old_rooms_count++;
            }
        }
        else {
            snprintf(response, sizeof(response),
                 "[ROOM] %s left '%s', rejoined '%s'\n",
                 client->username, old_room, client->room);
        }
        broadcast(response, client->socket_fd, old_room);
    } else {
        int rejoined = 0;
        if (client->old_rooms_count > 0) {
            int i = 0;
            while (i < client->old_rooms_count) {
                if (strcmp(client->old_rooms[i], client->room) == 0) {
                    rejoined = 1;
                    break;
                }
                i++;
            }
        }

        if (!rejoined) {
            snprintf(response, sizeof(response),
                 "[ROOM] %s joined '%s'\n",
                 client->username, client->room);
            strncpy(client->old_rooms[client->old_rooms_count], client->room, sizeof(client->old_rooms[client->old_rooms_count]));
            client->old_rooms_count++;
        }
        else {
            snprintf(response, sizeof(response),
                "[ROOM] %s rejoined '%s'\n",
                client->username, client->room);
        }
    }

    broadcast(response, client->socket_fd, room);
    // [Server] : You joined the room teamchat'
    snprintf(response, sizeof(response), "[SUCCESS] You joined the room '%s'\n", client->room);
    send(client->socket_fd, response, strlen(response), 0);
}

void cmd_leave(client_node_t *client) {
    if (client == NULL || strlen(client->room) == 0) {
        return; // Invalid client or not in a room
    }

    if (strlen(client->room) == 0) {
        send(client->socket_fd, "[INFO] You are not in a room.\n", 30, 0);
    } else {
        char info[128];
        snprintf(info, sizeof(info), "[ROOM] %s left room '%s'\n", client->username, client->room);
        pthread_mutex_lock(&client_list_mutex);
        char old_room[33];
        strncpy(old_room, client->room, sizeof(client->room));
        old_room[32] = '\0'; // Ensure null termination
        client->room[0] = '\0';
        strncpy(client->old_rooms[client->old_rooms_count], old_room, sizeof(client->old_rooms[client->old_rooms_count]));
        client->old_rooms_count++;
        pthread_mutex_unlock(&client_list_mutex);
        send(client->socket_fd, "[SUCCESS] Left the room.\n", 26, 0);
        broadcast(info, client->socket_fd, old_room);

        char log_msg[BUFFER_SIZE];
        snprintf(log_msg, sizeof(log_msg), "[LEAVE] user '%s' left room '%s'\n", client->username, old_room);
        log_to_file(log_msg);
    }
}

void cmd_broadcast(client_node_t *client, const char *message) {
    if (client == NULL || message == NULL || strlen(message) == 0) {
        return; // Invalid parameters
    }

    char formatted[BUFFER_SIZE];
    snprintf(formatted, sizeof(formatted), "[MESSAGE]: Broadcasted message from %s as '%s'\n", client->username, message);

    pthread_mutex_lock(&client_list_mutex);
    client_node_t *curr = client_list;
    while (curr) {
        if (curr != client && strcmp(curr->room, client->room) == 0) {
            send(curr->socket_fd, formatted, strlen(formatted), 0);
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&client_list_mutex);

    char response[BUFFER_SIZE];
    snprintf(response, sizeof(response), "[SUCCESS]: Message sent to room '%s'\n", client->room);
    send(client->socket_fd, response, strlen(response), 0);

    char log_msg[BUFFER_SIZE];
    snprintf(log_msg, sizeof(log_msg), "[BROADCAST] user '%s': %s\n", client->username, message);
    log_to_file(log_msg);
}

void cmd_whisper(client_node_t *client, const char *target, const char *message) {
    if (client == NULL || target == NULL || message == NULL || strlen(target) == 0 || strlen(message) == 0) {
        return; // Invalid parameters
    }

    pthread_mutex_lock(&client_list_mutex);
    client_node_t *curr = client_list;
    int found = 0;
    while (curr) {
        if (strcmp(curr->username, target) == 0) {
            char formatted[BUFFER_SIZE];
            int max_content_len = (int)sizeof(formatted) - 32; // 32 for prefix and username
            if (max_content_len < 0) max_content_len = 0;
            snprintf(formatted, sizeof(formatted), "[WHISPER][%s -> you]: %.*s\n", client->username, max_content_len, message);
            send(curr->socket_fd, formatted, strlen(formatted), 0);
            found = 1;
            break;
        }
        curr = curr->next;
    }
    pthread_mutex_unlock(&client_list_mutex);

    if (!found) {
        send(client->socket_fd, "[ERROR] User not found.\n", strlen("[ERROR] User not found.\n"), 0);

        char log_msg[BUFFER_SIZE * 2];
        snprintf(log_msg, sizeof(log_msg), "[WHISPER] user '%s' tried to whisper to non-existent user '%s': %s\n", client->username, target, message);
        log_to_file(log_msg);
    }
    else {
        char response[BUFFER_SIZE];
        snprintf(response, sizeof(response), "[SUCCESS]: Whisper sent to '%s'\n", target);
        send(client->socket_fd, response, strlen(response), 0);
        char log_msg[BUFFER_SIZE * 2];
        snprintf(log_msg, sizeof(log_msg), "[WHISPER] user '%s' whispered to '%s': %s\n", client->username, target, message);
        log_to_file(log_msg);
    }
}

void cmd_exit(client_node_t *client)
{
    if (client == NULL)
    {
        return; // Invalid client
    }

    int client_fd = client->socket_fd;
    char room[BUFFER_SIZE] = {0};

    pthread_mutex_lock(&client_list_mutex);
    strncpy(room, client->room, sizeof(client->room) - 1);
    client->room[0] = '\0'; // Clear room - şimdi mutex koruması altında
    pthread_mutex_unlock(&client_list_mutex);


    char username[USERNAME_LEN + 1];

    strncpy(username, client->username, USERNAME_LEN);
    username[USERNAME_LEN] = '\0';

    send(client_fd, "[INFO]: Disconnected. Goodbye!\n", strlen("[INFO]: Disconnected. Goodbye!\n"), 0);


    broadcast("[DISCONNECT]: User has left the server.\n", client_fd, room);

    char log_msg[BUFFER_SIZE];
    snprintf(log_msg, sizeof(log_msg), "[DISCONNECT] user '%s' exited the server.\n", username);
    log_to_file(log_msg);

    pthread_mutex_lock(&client_list_mutex);
    remove_client(client_fd);
    pthread_mutex_unlock(&client_list_mutex);

    pthread_exit(NULL);
}
