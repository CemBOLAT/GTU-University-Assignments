#ifndef SHM_UTILS_H
#define SHM_UTILS_H

#include <semaphore.h>
#include "../../include/common.h"

#define SHM_NAME_TEMPLATE "/shm_bankreq_%d"
#define SHM_SIZE sizeof(SharedMemoryData)

typedef struct {
    ClientRequest request;
    ServerResponse response;

    BankAccountLog account;

    sem_t sem_request_ready;   // server → teller
    sem_t sem_response_ready;  // teller → server
} SharedMemoryData;

// Create shared memory and initialize semaphores : create: 1, open: 0
// shm_name: name of the shared memory, e.g., "/shm_bankreq_1"
SharedMemoryData* create_shared_memory(const char* shm_name, int create);

// Close the shared memory and unlink it
void destroy_shared_memory(const char* shm_name, SharedMemoryData* shm_ptr, int is_child);

#endif // SHM_UTILS_H
