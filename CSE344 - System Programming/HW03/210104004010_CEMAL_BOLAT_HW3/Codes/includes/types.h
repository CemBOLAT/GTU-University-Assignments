// types.h
#ifndef TYPES_H
#define TYPES_H

#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define MAX_SATELLITES 5
#define MAX_ENGINEERS 3
#define PROCESSING_TIME 2
#define TIMEOUT_SECONDS 5

typedef struct SatelliteRequest {
    int id;
    int priority;
    time_t arrivalTime;
    sem_t requestHandled;
    int valid;
    int being_processed;
} SatelliteRequest;

typedef struct Node {
    SatelliteRequest* request;
    struct Node* next;
} Node;


typedef struct s_Engineers {
    int id;
    pthread_t threadId;
} Engineers;

typedef struct s_Satellites {
    int id;
    pthread_t threadId;
} Satellites;


typedef struct {
    pthread_mutex_t engineerMutex;
    sem_t newRequest;

    int availableEngineers;
    int satelliteCount; 
    int stop;

    Node* requestQueueHead;

    Engineers engineers[MAX_ENGINEERS];
    Satellites *satellites;

} t_data;


#endif // TYPES_H
