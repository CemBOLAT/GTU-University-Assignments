#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "queue.h"
#include "types.h"

void insertRequest(t_data* data, SatelliteRequest* request) {
    if (data == NULL || request == NULL) {
        fprintf(stderr, "insertRequest: NULL pointer!\n");
        return;
    }

    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("malloc: Node");
        return;
    }

    newNode->request = request;
    newNode->next = NULL;

    if (data->requestQueueHead == NULL || request->priority >= data->requestQueueHead->request->priority) {
        newNode->next = data->requestQueueHead;
        data->requestQueueHead = newNode;
    } else {
        Node* current = data->requestQueueHead;
        while (current->next != NULL && current->next->request->priority > request->priority) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

SatelliteRequest* popHighestPriorityRequest(t_data* data) {
    if (data == NULL) {
        fprintf(stderr, "popHighestPriorityRequest: NULL data pointer!\n");
        return NULL;
    }

    if (data->requestQueueHead == NULL) {
        pthread_mutex_unlock(&data->engineerMutex);
        return NULL;
    }

    Node* topNode = data->requestQueueHead;
    data->requestQueueHead = topNode->next;

    SatelliteRequest* req = topNode->request;
    free(topNode);

    return req;
}


void removeRequestFromQueue(t_data* data, int request_id) {
    if (data == NULL) {
        fprintf(stderr, "removeRequestFromQueue: data is NULL\n");
        return;
    }
    
    if (data->requestQueueHead == NULL) {
        return;
    }
    
    Node* current = data->requestQueueHead;
    Node* prev = NULL;
    
    while (current != NULL) {
        if (current->request != NULL && current->request->id == request_id) {
            if (prev == NULL) {
                data->requestQueueHead = current->next;
            } else {
                prev->next = current->next;
            }
            
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}