#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "../includes/types.h"
#include "../includes/engineer.h"
#include "../includes/satellite.h"
#include "../includes/queue.h"
#include "../includes/utils.h"

int main() {
    t_data data;
    data.requestQueueHead = NULL;
    data.stop = 0;
    data.availableEngineers = MAX_ENGINEERS;
    
    // Initialize random seed using current time
    time_t t = time(NULL);
    if (t == ((time_t)-1)) {
        perror("time");
        return EXIT_FAILURE;
    }


    srand(t);

    // Randomly determine the number of satellites to create
    data.satelliteCount = (rand() % MAX_SATELLITES) + 1;
    data.satellites = (Satellites*)malloc(sizeof(Satellites) * data.satelliteCount);
    if (data.satellites == NULL) {
        perror("Failed to allocate memory for satellite threads");
        cleanup(&data);
        return EXIT_FAILURE;
    }
    
    // Initialize synchronization primitives
    // Mutex for protecting shared engineer availability data
    if (pthread_mutex_init(&data.engineerMutex, NULL) != 0) {
        perror("pthread_mutex_init");
        cleanup(&data);
        exit(EXIT_FAILURE);
    }

    // Semaphore for signaling new requests to engineer threads
    if (sem_init(&data.newRequest, 0, 0) != 0) { 
        perror("sem_init");
        cleanup(&data);
        exit(EXIT_FAILURE);
    }

    printf("Launching %d satellites...\n", data.satelliteCount);

    
    // Create engineer threads
    for (int i = 0; i < MAX_ENGINEERS; i++) {
        data.engineers[i].id = i + 1;
        if (pthread_create(&data.engineers[i].threadId, NULL, engineer, &data) != 0) {
            perror("Failed to create engineer thread");
            cleanup(&data);
            exit(EXIT_FAILURE);
        }    
    }

    // Create satellite threads
    for (int i = 0; i < data.satelliteCount; i++) {
        data.satellites[i].id = i + 1;
        if (pthread_create(&data.satellites[i].threadId, NULL, satellite, &data) != 0) {
            perror("Failed to create satellite thread");
            cleanup(&data);
            exit(EXIT_FAILURE);
        }
    }

    // Wait for all satellite threads to finish
    for (int i = 0; i < data.satelliteCount; i++) {
        if (pthread_join(data.satellites[i].threadId, NULL) != 0) {
            perror("Failed to join satellite thread");
        }
    }

    data.stop = 1; // Signal engineers to stop processing

    // Notify engineers to wake up and check for the stop signal
    for (int i = 0; i < MAX_ENGINEERS; i++) {
        if (sem_post(&data.newRequest) != 0) {
            perror("sem_post: newRequest");
        }
    }

    // Wait for all engineer threads to finish
    for (int i = 0; i < MAX_ENGINEERS; i++) {
        pthread_join(data.engineers[i].threadId, NULL);
    }

    cleanup(&data); // Clean up resources

    return 0;
}
