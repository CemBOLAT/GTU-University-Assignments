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
#include <stdlib.h>

// Generate a bank ID string based on a numeric ID
void generate_bank_id(char* out, int id_num) {
    snprintf(out, MAX_BANK_ID_LEN, "BankID_%02d", id_num);
}

// Clean up resources and exit the program
void cleanup_and_exit(int status) {
    printf("Signal received closing active Tellers...\n");

    int i = 0;
    while (i < teller_pid_count) {
        kill(g_teller_pids[i], SIGUSR1);
        waitTeller(g_teller_pids[i], &status);
        ++i;
    }

    printf("Removing ServerFIFO... Updating log file...\n");
    destroy_shared_memory(g_db.shm_name, NULL, 0);
    
    write_log(&g_db, LOG_PATH);
    close(g_db.server_fd);
    free_database(&g_db);
    remove_fifo(SERVER_FIFO_NAME);
    printf("%s says \"Bye\"...\n", g_db.bank_name);
    exit(status);
}

// Signal handler to trigger cleanup
void handle_signal(int signo) {
    keep_running = 0;
    cleanup_and_exit(0);
}

// Extract numeric ID from a bank ID string (e.g., "BankID_03" -> 3)
int extract_id(const char* bank_id) {
    int id_num = 0;
    sscanf(bank_id, "BankID_%d", &id_num);
    return id_num;
}

// Read a single line from database format: "<BankID> <Balance>"
int read_db_format(int fd, char* id, int* balance, int max_id_len) {
    size_t bytes_read = 0;
    char c;

    // Read bank ID
    while (bytes_read < max_id_len - 1 && read(fd, &c, 1) == 1 && c != ' ' && c != '\n') {
        id[bytes_read++] = c;
    }
    id[bytes_read] = '\0';

    if (bytes_read == 0) return 0;   // No ID read
    if (c != ' ') return -1;         // Format error: expected space

    // Read balance as string
    char balance_buf[32];
    size_t balance_bytes = 0;
    
    while (balance_bytes < sizeof(balance_buf) - 1 && read(fd, &c, 1) == 1 && c != '\n') {
        balance_buf[balance_bytes++] = c;
    }
    balance_buf[balance_bytes] = '\0';

    if (balance_bytes == 0) return -1; // No balance read

    // Convert balance string to integer
    *balance = atoi(balance_buf);

    return 2; // Successfully read ID and balance
}

// Extract PID from a FIFO name (e.g., "/ClientFIFO_1234" -> 1234)
int extract_pid(const char* fifo_name) {
    char* pid_str = strrchr(fifo_name, '_');
    if (pid_str == NULL) return -1;
    return atoi(pid_str + 1);
}
