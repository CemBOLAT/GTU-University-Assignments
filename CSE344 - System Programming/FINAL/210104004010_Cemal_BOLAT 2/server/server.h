#ifndef SERVER_H
#define SERVER_H

void broadcast(const char *msg, int sender_fd, const char *room);
void *client_handler(void *arg);
void handle_client_command(client_node_t *client, const char *msg);

#endif