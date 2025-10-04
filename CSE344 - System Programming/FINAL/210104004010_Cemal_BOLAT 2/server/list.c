#include "list.h"
#include "server.h"
#include <unistd.h>
#include <sys/socket.h>
#include <string.h>


void add_client(client_node_t *new_client) {
    new_client->next = client_list;
    client_list = new_client;
}

void remove_client(int client_fd) {
    client_node_t **curr = &client_list;
    while (*curr) {
        if ((*curr)->socket_fd == client_fd) {
            client_node_t *to_delete = *curr;
            *curr = (*curr)->next;
            close(to_delete->socket_fd);
            free(to_delete);
            break;
        }
        curr = &((*curr)->next);
    }
}

void free_list_with_message() {

    pthread_mutex_lock(&client_list_mutex);

    client_node_t *curr = client_list;
    while (curr) {
        client_node_t *to_delete = curr;
        curr = curr->next;
        close(to_delete->socket_fd);
        free(to_delete);
    }
    client_list = NULL;

    pthread_mutex_unlock(&client_list_mutex);

}

// Kuyruk fonksiyonları
void init_file_queue(file_queue_t *queue)
{
    memset(queue, 0, sizeof(file_queue_t));
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    pthread_mutex_init(&queue->mutex, NULL);
    pthread_cond_init(&queue->not_full, NULL);
    pthread_cond_init(&queue->not_empty, NULL);
}


int len_list(client_node_t *list) {
    if (list == NULL) {
        return 0;
    }
    int count = 0;
    while (list) {
        count++;
        list = list->next;
    }
    return count;
}

client_node_t *find_client_by_username(const char *username) {
    client_node_t *curr = client_list;
    while (curr) {
        if (strcmp(curr->username, username) == 0) {
            pthread_mutex_unlock(&client_list_mutex);
            return curr;
        }
        curr = curr->next;
    }
    return NULL; // Not found
}
