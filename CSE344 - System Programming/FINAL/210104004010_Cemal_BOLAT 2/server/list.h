
#ifndef LIST_H
#define LIST_H

#include "global.h"

void            add_client(client_node_t *new_client);
void            remove_client(int client_fd);
void            free_list_with_message();

void            init_file_queue(file_queue_t *queue);
void            enqueue_file(file_queue_t *queue, file_transfer_t *file);
file_transfer_t *dequeue_file(file_queue_t *queue);
int             len_list(client_node_t *list);
client_node_t   *find_client_by_username(const char *username);

#endif
