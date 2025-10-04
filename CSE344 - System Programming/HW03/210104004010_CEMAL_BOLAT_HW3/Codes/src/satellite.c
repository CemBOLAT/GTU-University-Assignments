#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include "satellite.h"
#include "queue.h"
#include "types.h"

void* satellite(void* arg) {
    t_data* data = (t_data*)arg;

    // Allocate memory for satellite request
    SatelliteRequest* request = malloc(sizeof(SatelliteRequest)); 
    if (request == NULL) {
        perror("malloc: SatelliteRequest");
        pthread_exit(NULL);
    }

    // Get the satellite ID from the thread ID
    int satelliteId = -1;
    pthread_t threadId = pthread_self();
    for (int i = 0; i < data->satelliteCount; i++) {
        if (data->satellites[i].threadId == threadId) {
            satelliteId = data->satellites[i].id;
            break;
        }
    }

    // Initialize the request
    request->id = satelliteId;
    request->priority = rand() % 5 + 1;
    request->arrivalTime = time(NULL);
    request->valid = 1;  
    request->being_processed = 0;

    // Initialize the semaphore for request handling
    if (sem_init(&request->requestHandled, 0, 0) != 0) {
        perror("sem_init: requestHandled");
        free(request);
        pthread_exit(NULL);
    }

    printf("[SATELLITE] Satellite %d requesting (priority %d)...\n", request->id, request->priority);
    
    pthread_mutex_lock(&data->engineerMutex); // Lock the mutex to protect shared data
    insertRequest(data, request); // Insert the request into the queue
    pthread_mutex_unlock(&data->engineerMutex);

    // Signal to the engineer that a new request is available
    if (sem_post(&data->newRequest) != 0) {
        perror("sem_post: newRequest");
        pthread_exit(NULL);
    }

    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) == -1) { //
        perror("clock_gettime");
        pthread_exit(NULL);
    }
    ts.tv_sec += TIMEOUT_SECONDS; 

    // Wait for the engineer to handle the request or timeout
    int waitResult = sem_timedwait(&request->requestHandled, &ts);
    if (waitResult == -1) {
        if (errno == ETIMEDOUT) { // Check if the wait timed out
            printf("[TIMEOUT] Satellite %d timeout %d seconds!\n", request->id, TIMEOUT_SECONDS);
            
            pthread_mutex_lock(&data->engineerMutex); // Lock the mutex to protect shared data
            
            request->valid = 0;
            
            if (!request->being_processed) { // If the request is not being processed, remove it from the queue
                removeRequestFromQueue(data, request->id);
                
                sem_destroy(&request->requestHandled);
                
                free(request);
            }
            
            pthread_mutex_unlock(&data->engineerMutex);
        }
        else {
            perror("sem_timedwait");
            sem_destroy(&request->requestHandled); // Destroy the semaphore if wait failed
            free(request);
        }
        
        pthread_exit(NULL);
        return NULL;
    }
    
    // If the request was handled successfully, wait for the engineer to finish processing
    pthread_mutex_lock(&data->engineerMutex);
    sem_destroy(&request->requestHandled);
    free(request);
    pthread_mutex_unlock(&data->engineerMutex);
    pthread_exit(NULL);
    return NULL;
}