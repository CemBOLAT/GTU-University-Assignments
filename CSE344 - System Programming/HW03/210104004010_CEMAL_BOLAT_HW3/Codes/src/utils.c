#include <stdlib.h>
#include <stdio.h>
#include "../includes/utils.h"

void cleanup(t_data* data) {
    if (data == NULL) {
        fprintf(stderr, "cleanup: Null data pointer!\n");
        return;
    }

    pthread_mutex_lock(&data->engineerMutex);
    Node* current = data->requestQueueHead;
    while (current != NULL) {
        Node* temp = current;
        if (current->request != NULL) {
            sem_destroy(&current->request->requestHandled);
            free(current->request);
        }
        current = current->next;
        free(temp);
    }
    data->requestQueueHead = NULL;
    pthread_mutex_unlock(&data->engineerMutex);

    if (data->satellites != NULL) {
        free(data->satellites);
        data->satellites = NULL;
    }
    
    if (pthread_mutex_destroy(&data->engineerMutex) != 0) {
        perror("pthread_mutex_destroy");
    }

    if (sem_destroy(&data->newRequest) != 0) {
        perror("sem_destroy");
    }


    printf("[CLEANUP] System resources cleaned up.\n");
}