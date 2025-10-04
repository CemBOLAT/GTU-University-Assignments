#pragma once

#include "global.h"

void broadcast(const char *msg, int sender_fd, const char *room);
void cmd_join(client_node_t *client, const char *room);
void cmd_leave(client_node_t *client);
void cmd_broadcast(client_node_t *client, const char *message);
void cmd_whisper(client_node_t *client, const char *target, const char *message);
void cmd_exit(client_node_t *client);