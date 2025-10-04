#include "../include/common.h"
#include "../ipc/include/fifo_utils.h"
#include "../ipc/include/shm_utils.h"
#include "../include/teller_api.h"
#include "include/database.h"
#include "./include/teller.h"
#include "./include/utils.h"

#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>

// Global variables
volatile sig_atomic_t keep_running = 1;
BankDatabase g_db;
pid_t g_teller_pids[MAX_REQUESTS];
int teller_pid_count = 0;
char g_shm_names[MAX_REQUESTS][64];
int is_terminated = 0;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <BankName>\n", argv[0]);
        return EXIT_FAILURE;
    }

    // Initialize bank name
    strncpy(g_db.bank_name, argv[1], sizeof(g_db.bank_name) - 1);
    g_db.bank_name[sizeof(g_db.bank_name) - 1] = '\0';

    // Setup signal handlers
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGPIPE, SIG_IGN);

    printf("%s is active...\n", argv[1]);

    // Create server FIFO
    if (create_fifo(SERVER_FIFO_NAME) == -1)
        return EXIT_FAILURE;

    // Load existing database log
    if (load_log(&g_db, LOG_PATH) == -1) cleanup_and_exit(EXIT_FAILURE);

    if (g_db.count == 0) {
        printf("No previous logs.. Creating the bank database...\n");
    } else {
        printf("Bank database loaded with %d accounts...\n", g_db.count);
    }
    
    printf("Waiting for clients @ServerFIFO_CemalBOLAT...\n");
    
    // Open server FIFO for reading client FIFO names
    int server_fd = open_fifo_read(SERVER_FIFO_NAME);
    if (server_fd == -1) {
        perror("open server fifo");
        return EXIT_FAILURE;
    }

    g_db.server_fd = server_fd;

    int client_response_fd = -1;
    char bank_reporter[MAX_REQUESTS][1024];
    int bank_reporter_count = 0;

    while (keep_running) {
        char client_fifo_name[MAX_FIFO_NAME_LEN];
        memset(client_fifo_name, 0, sizeof(client_fifo_name));

        // Wait for a client FIFO name from the server FIFO
        ssize_t name_bytes = read(server_fd, client_fifo_name, sizeof(client_fifo_name) - 1);
        if (name_bytes <= 0) {
            if (name_bytes == -1 && errno == EPIPE) {
                perror("read client fifo name");
                break;
            }
            usleep(1000);
            continue;
        }
        client_fifo_name[name_bytes] = '\0';


        int client_fd = open(client_fifo_name, O_RDONLY);
        if (client_fd == -1) {
            perror("open client fifo for reading");
            continue;
        }


        ClientRequest requests[MAX_REQUESTS];
        int request_count = 0;
        ClientRequest temp_req;

        // Read multiple requests from the client FIFO
        while (1) {
            ssize_t bytes_read = read(client_fd, &temp_req, sizeof(ClientRequest));
            if (bytes_read <= 0) {
                if (bytes_read == -1 && errno == EPIPE) {
                    perror("read client fifo");
                }
                break;
            }
            if (bytes_read != sizeof(ClientRequest)) {
                fprintf(stderr, "Incomplete read from client FIFO\n");
                break;
            }
            if (request_count < MAX_REQUESTS) {
                requests[request_count++] = temp_req;
            }
        }

        
        close(client_fd);

        printf("- Received %d clients from PIDClient%d\n", request_count, extract_pid(client_fifo_name));

        for (int i = 0; i < request_count; ++i) {
            ClientRequest* req = &requests[i];

            // Generate new bank ID if needed
            if (strlen(req->bank_id) == 0) {
                if (g_db.count == 0)
                    generate_bank_id(req->bank_id, 1);
                else
                    generate_bank_id(req->bank_id, extract_id(g_db.accounts[g_db.count - 1].bank_id) + 1);
            }

            snprintf(g_db.shm_name, sizeof(g_db.shm_name), SHM_NAME_TEMPLATE, req->client_pid);

            // Create shared memory for the client
            SharedMemoryData* shm = create_shared_memory(g_db.shm_name, 1);
            if (!shm) {
                fprintf(stderr, "Failed to create shared memory for client %d\n", req->client_pid);
                continue;
            }

            sem_init(&shm->sem_request_ready, 1, 0);
            sem_init(&shm->sem_response_ready, 1, 0);
            

            memcpy(&shm->request, req, sizeof(ClientRequest));

            // Load account data into shared memory
            BankAccountLog* acc = find_account(&g_db, req->bank_id);
            if (acc) {
                memcpy(&shm->account, acc, sizeof(BankAccountLog));
            } else if (req->new_account) {
                memset(&shm->account, 0, sizeof(BankAccountLog));
                strncpy(shm->account.bank_id, req->bank_id, MAX_BANK_ID_LEN);
            }
            else {
                memset(&shm->account, 0, sizeof(BankAccountLog));
                shm->account.is_invalid_account = 1;
            }
            
            
            pid_t pid; 
            if (req->type == TRANSACTION_DEPOSIT) {
                pid = Teller(deposit, strdup(g_db.shm_name));
            } else if (req->type == TRANSACTION_WITHDRAW) {
                pid = Teller(withdraw, strdup(g_db.shm_name));
            } else {
                fprintf(stderr, "Invalid transaction type.\n");
                sem_destroy(&shm->sem_request_ready);
                sem_destroy(&shm->sem_response_ready);
                destroy_shared_memory(g_db.shm_name, shm, 0);
                continue;
            }
            if (pid == -1) {
                fprintf(stderr, "Failed to create teller process.\n");
                sem_destroy(&shm->sem_request_ready);
                sem_destroy(&shm->sem_response_ready);
                destroy_shared_memory(g_db.shm_name, shm, 0);
                continue;
            }

            strcpy(g_shm_names[teller_pid_count], g_db.shm_name);
            g_teller_pids[teller_pid_count++] = pid;
            
            // Notify teller that request is ready
            sem_post(&shm->sem_request_ready); 

            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += 15;
            
            if (sem_timedwait(&shm->sem_response_ready, &ts) == -1) {
                perror("Timeout waiting for teller response (server)");
                sem_destroy(&shm->sem_request_ready);
                sem_destroy(&shm->sem_response_ready);


                destroy_shared_memory(g_db.shm_name, shm, 0);
                continue;
            }
            
            ServerResponse *resp = &shm->response;

            if (resp->success && strlen(resp->bank_id) > 0) {
                BankAccountLog* acc = find_account(&g_db, resp->bank_id);
            
                if (!acc) {
                    if (ensure_capacity(&g_db) == -1) {
                        fprintf(stderr, "Failed to expand g_db.\n");
                        shm->response.success = 0;
                        snprintf(shm->response.message, sizeof(shm->response.message), "Failed to expand g_db.");
    
                        sem_destroy(&shm->sem_request_ready);
                        sem_destroy(&shm->sem_response_ready);
                        destroy_shared_memory(g_db.shm_name, shm, 0);
                        continue;
                    }
            
                    acc = &g_db.accounts[g_db.count++];
                    strncpy(acc->bank_id, shm->response.bank_id, MAX_BANK_ID_LEN);
                    acc->current_balance = 0;
                    acc->op_count = 0;
                }
                
                if (req->type == TRANSACTION_DEPOSIT) {
                    acc->current_balance += req->amount;
                    snprintf(acc->operations[acc->op_count++], 8, "D %d", req->amount);
                } else if (req->type == TRANSACTION_WITHDRAW) {
                    acc->current_balance -= req->amount;
                    snprintf(acc->operations[acc->op_count++], 8, "W %d", req->amount);
                }
            
                shm->response.new_balance = acc->current_balance;
            
                if (acc->current_balance == 0) {
                    acc->is_closed = 1;
                }
                
                write_log(&g_db, LOG_PATH);
                if (is_terminated == 1){ // if signal is received while writing log it must terminate the process
                    handle_signal(SIGTERM);
                }
            }

            char clientIDBye[16];
            snprintf(clientIDBye, sizeof(clientIDBye), "Bye Client%02d", req->client_id);
            snprintf(bank_reporter[bank_reporter_count++], 
                sizeof(bank_reporter[0]), 
                "Client%02d %s %d credits... %s...%s\n", 
                req->client_id,
                req->type == TRANSACTION_DEPOSIT ? "deposited" : "withdraws",
                req->amount,
                resp->success ? "updating log" : "operation not permitted",
                (resp->new_balance == 0 && resp->success == 1) ? clientIDBye : "");
        }
        for (int i = 0; i < teller_pid_count; ++i) {
            // if (i == teller_pid_count / 2){
            //     handle_signal(SIGTERM); // test case 3
            // }
            int status = 0;
            waitTeller(g_teller_pids[i], &status);
        }
        for (int i = 0; i < teller_pid_count; ++i) {
            destroy_shared_memory(g_shm_names[i], NULL, 0);
        }
        for (int i = 0; i < bank_reporter_count; ++i) {
            printf("%s", bank_reporter[i]);
        }
        teller_pid_count = 0;
        bank_reporter_count = 0;
        if (client_response_fd != -1) {
            close(client_response_fd);
        }
        printf("\nWaiting for clients @ServerFIFO_CemalBOLAT...\n");
    }

    cleanup_and_exit(0);
    return 0;
}