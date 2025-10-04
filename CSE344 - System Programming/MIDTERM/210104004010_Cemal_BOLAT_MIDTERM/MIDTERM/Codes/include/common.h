#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

// FIFO names
#define SERVER_FIFO_NAME "./ServerFIFO_CemalBOLAT"
#define CLIENT_FIFO_TEMPLATE "./ClientFIFO_CemalBOLAT%d"
#define DB_PATH "AdaBank.bankDB"

#define MAX_FIFO_NAME_LEN 64
#define MAX_TRANSACTIONS 128
#define MAX_BANK_NAME_LEN 64
#define MAX_REQUESTS 128
#define TIMEOUT_SECONDS 5

// Bank ID format
#define BANK_ID_PREFIX "BankID_"
#define MAX_BANK_ID_LEN 32

#define MAX_LINE_LEN 256

// Transaction types
typedef enum {
    TRANSACTION_DEPOSIT,
    TRANSACTION_WITHDRAW
} TransactionType;

// Request structure: Client -> Teller
typedef struct {
    pid_t client_pid;                      // PID of the client process
    TransactionType type;                  // Deposit or Withdraw
    int amount;                            // Transaction amount
    char bank_id[MAX_BANK_ID_LEN];          // Bank account ID (e.g., "BankID_01")
    char client_fifo[MAX_FIFO_NAME_LEN];    // FIFO name for server response
    int client_id;
    int new_account;                       // Request to open a new account (1: yes, 0: no)
} ClientRequest;

// Response structure: Teller -> Client
typedef struct {
    int success;                           // 1: success, 0: failure
    int new_balance;                       // Updated account balance
    char message[128];                     // Status message
    char bank_id[MAX_BANK_ID_LEN];          // Assigned bank ID if a new account is created
} ServerResponse;

// Structure for log entries (for advanced use)
typedef struct {
    char bank_id[MAX_BANK_ID_LEN];
    int current_balance;
    int is_closed;                         // 1 if the account is closed
    int is_invalid_account;                // 1 if the account is invalid
    char operations[MAX_TRANSACTIONS][8];  // Operations like "D 300", "W 100"
    int op_count;
    pid_t teller_pid;                      // PID of the Teller handling the request
} BankAccountLog;

#endif // COMMON_H
