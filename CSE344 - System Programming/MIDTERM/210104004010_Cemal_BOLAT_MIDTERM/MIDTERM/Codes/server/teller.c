#include "../include/common.h"
#include "../ipc/include/shm_utils.h"
#include "./include/utils.h"
#include "../server/include/database.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>

// Global variables for shared memory and FIFO path
static SharedMemoryData* g_shm = NULL;
static char* g_shm_name = NULL;
static char client_fifo_path[MAX_FIFO_NAME_LEN];

// Handle signals for teller process (cleanup resources)
void handle_teller_signal(int signo) {
    printf("Teller PID %d received signal %d. Cleaning up...\n", getpid(), signo);

    if (signo == SIGUSR1) {
        kill(g_shm->request.client_pid, SIGUSR1);
    }

    g_shm->response.success = 0;
    snprintf(g_shm->response.message, sizeof(g_shm->response.message), "Something went wrong. Teller is terminated.");

    if (strlen(client_fifo_path) > 0) {
        if (unlink(client_fifo_path) == -1) {
            perror("Failed to unlink client FIFO");
        } else {
            printf("Client FIFO %s unlinked.\n", client_fifo_path);
        }
    }

    if (g_shm && g_shm_name) {
        sem_destroy(&g_shm->sem_request_ready);
        sem_destroy(&g_shm->sem_response_ready);

        destroy_shared_memory(g_shm_name, g_shm, 1);
        free(g_shm_name);
        g_shm = NULL;
        g_shm_name = NULL;
    }

    free_database(&g_db);
    _exit(0); // Safe exit from signal handler
}

// Handle deposit request
void* deposit(void* arg) {
    char* shm_name = (char*)arg;
    g_shm_name = shm_name;

    SharedMemoryData* shm = create_shared_memory(shm_name, 0);
    if (!shm) {
        free(shm_name);
        _exit(1);
    }
    g_shm = shm;

    // Setup signal handlers
    signal(SIGINT, handle_teller_signal);
    signal(SIGTERM, handle_teller_signal);
    signal(SIGUSR1, handle_teller_signal);

    sem_wait(&shm->sem_request_ready);

    ClientRequest* req = &shm->request;
    ServerResponse* resp = &shm->response;
    BankAccountLog* acc = &shm->account;

    acc->teller_pid = getpid();

    char welcome_back[128];
    snprintf(welcome_back, sizeof(welcome_back), "Welcome back Client%02d", req->client_id);

    printf("-- Teller PID%d is active serving Client%02d...%s\n",
           getpid(), req->client_id, req->new_account || acc->current_balance == 0 ? "" : welcome_back);

    strncpy(resp->bank_id, req->bank_id, MAX_BANK_ID_LEN);
    resp->success = 1;
    snprintf(resp->message, sizeof(resp->message), "Approved.");

    // Handle error conditions
    if (acc->is_invalid_account) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Account not found.");
    } else if (acc->is_closed) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Account is closed.");
    } else if (req->amount <= 0) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Invalid amount.");
    }

    sem_post(&shm->sem_response_ready);

    // Send response to client
    int client_response_fd = open(req->client_fifo, O_WRONLY);
    if (client_response_fd != -1) {
        strncpy(client_fifo_path, req->client_fifo, sizeof(client_fifo_path) - 1);
        client_fifo_path[sizeof(client_fifo_path) - 1] = '\0';

        if (write(client_response_fd, resp, sizeof(ServerResponse)) == -1) {
            perror("Failed to write response to client FIFO");
        }
        close(client_response_fd);
    } else {
        perror("Failed to open client FIFO for writing response");
    }

    if (g_shm) {
        sem_destroy(&g_shm->sem_request_ready);
        sem_destroy(&g_shm->sem_response_ready);

        destroy_shared_memory(g_shm_name, g_shm, 1);
        free(g_shm_name);
    }
    g_shm = NULL;
    g_shm_name = NULL;
    free_database(&g_db);

    return NULL;
}

// Handle withdraw request
void* withdraw(void* arg) {
    char* shm_name = (char*)arg;
    g_shm_name = shm_name;

    SharedMemoryData* shm = create_shared_memory(shm_name, 0);
    if (!shm) {
        free(shm_name);
        _exit(1);
    }
    g_shm = shm;

    // Setup signal handlers
    signal(SIGINT, handle_teller_signal);
    signal(SIGTERM, handle_teller_signal);
    signal(SIGUSR1, handle_teller_signal);

    sem_wait(&shm->sem_request_ready);

    ClientRequest* req = &shm->request;
    ServerResponse* resp = &shm->response;
    BankAccountLog* acc = &shm->account;

    acc->teller_pid = getpid();

    char welcome_back[128];
    snprintf(welcome_back, sizeof(welcome_back), "Welcome back Client%02d", req->client_id);

    printf("-- Teller PID%d is active serving Client%02d...%s\n",
        getpid(), req->client_id, req->new_account || acc->current_balance == 0 ? "" : welcome_back);

    strncpy(resp->bank_id, req->bank_id, MAX_BANK_ID_LEN);
    resp->success = 1;
    snprintf(resp->message, sizeof(resp->message), "Approved.");

    // Handle error conditions
    if (acc->is_invalid_account) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Account not found.");
    } else if (acc->is_closed) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Account is closed.");
    } else if (req->amount <= 0) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Invalid amount.");
    } else if (req->new_account) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Cannot withdraw from a new account.");
    } else if (acc->current_balance < req->amount) {
        resp->success = 0;
        snprintf(resp->message, sizeof(resp->message), "Insufficient funds.");
    }

    //handle_teller_signal(SIGTERM); // test case 4

    sem_post(&shm->sem_response_ready);

    // Send response to client
    int client_response_fd = open(req->client_fifo, O_WRONLY);
    if (client_response_fd != -1) {
        strncpy(client_fifo_path, req->client_fifo, sizeof(client_fifo_path) - 1);
        client_fifo_path[sizeof(client_fifo_path) - 1] = '\0';

        if (write(client_response_fd, resp, sizeof(ServerResponse)) == -1) {
            perror("Failed to write response to client FIFO");
        }
        close(client_response_fd);
    } else {
        perror("Failed to open client FIFO for writing response");
    }

    if (g_shm) {
        sem_destroy(&g_shm->sem_request_ready);
        sem_destroy(&g_shm->sem_response_ready);

        destroy_shared_memory(g_shm_name, g_shm, 1);
        free(g_shm_name);
    }
    g_shm = NULL;
    g_shm_name = NULL;
    free_database(&g_db);

    return NULL;
}
