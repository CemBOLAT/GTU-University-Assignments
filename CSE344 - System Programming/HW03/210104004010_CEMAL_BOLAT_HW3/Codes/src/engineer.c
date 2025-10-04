#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "engineer.h"
#include "queue.h"
#include "types.h"

void* engineer(void* arg) {
    t_data* data = (t_data*)arg;

    int engineerId = -1;
    pthread_t threadId = pthread_self();
    for (int i = 0; i < MAX_ENGINEERS; i++) {
        if (data->engineers[i].threadId == threadId) {
            engineerId = data->engineers[i].id;
            break;
        }
    }

    while (1) {
        if (sem_wait(&data->newRequest) != 0) {
            perror("sem_wait: newRequest");
            pthread_exit(NULL);
        }
        
        if (data->stop) {  
            break;
        }
        
        pthread_mutex_lock(&data->engineerMutex);
        SatelliteRequest* request = popHighestPriorityRequest(data);
        
        if (request == NULL) {
            pthread_mutex_unlock(&data->engineerMutex);
            fprintf(stderr, "[ENGINEER %d] Warning: No request found in queue.\n", engineerId);
            continue;
        }
        
        request->being_processed = 1;
        int request_id = request->id;
        int request_priority = request->priority;
        int request_valid = request->valid;
        
        data->availableEngineers--;
        printf("[ENGINEER %d] Handling Satellite %d (priority %d)...\n", 
               engineerId, request_id, request_priority);
        pthread_mutex_unlock(&data->engineerMutex);


        sleep(PROCESSING_TIME); 

        pthread_mutex_lock(&data->engineerMutex);
        
        if (request_valid && request->valid) {
            printf("[ENGINEER %d] Finished Satellite %d\n",
                   engineerId, request_id);
            
            if (sem_post(&request->requestHandled) != 0) {
                perror("sem_post: requestHandled");
            }
        } else {            
            sem_destroy(&request->requestHandled);
            free(request);
            data->availableEngineers++;
        
            pthread_mutex_unlock(&data->engineerMutex);
            break;
        }
        
        request->being_processed = 0;
        
        data->availableEngineers++;
        
        pthread_mutex_unlock(&data->engineerMutex);
    }

    printf("[ENGINEER %d] Exiting...\n", engineerId);
    pthread_exit(NULL);
    return NULL;
}