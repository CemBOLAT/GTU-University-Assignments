#ifndef DATABASE_H
#define DATABASE_H

#include "../../include/common.h"
#include <semaphore.h>

// Structure representing the bank database
typedef struct {
    BankAccountLog* accounts;          // Array of account logs
    int count;                         // Current number of accounts
    int capacity;                      // Allocated capacity

    char shm_name[64];                 // Name of the shared memory segment
    int server_fd;                     // File descriptor for the server FIFO

    char bank_name[MAX_BANK_NAME_LEN]; // Bank name
} BankDatabase;

// Global variables
extern BankDatabase g_db; // Global database instance
extern volatile sig_atomic_t keep_running; // Flag to control signal handling
extern pid_t g_teller_pids[MAX_REQUESTS]; // Array of teller process IDs for waitTeller()
extern int teller_pid_count; // Number of teller processes
extern int is_terminated; // Flag to indicate if the server is terminated for atomicity

// Database management functions
int init_database(BankDatabase* db);
void free_database(BankDatabase* db);
int write_log(BankDatabase* db, const char* log_path);
int load_database(BankDatabase* db, const char* db_path);
int write_database(BankDatabase* db, const char* db_path);
int ensure_capacity(BankDatabase* db);
int load_log(BankDatabase* db, const char* log_path);
BankAccountLog* find_account(BankDatabase* db, const char* bank_id);

#endif // DATABASE_H
