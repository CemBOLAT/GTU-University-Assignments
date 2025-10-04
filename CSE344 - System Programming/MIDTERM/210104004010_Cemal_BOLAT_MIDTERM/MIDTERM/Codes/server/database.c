#include "./include/database.h"
#include "./include/utils.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

// Signal handler to set termination flag
void handle_termination(int signo) {
    if (signo == SIGTERM || signo == SIGINT) {
        // Set global termination flag to 1 after logging depending on its value it might be used to terminate the process
        is_terminated = 1;
    }
}

// Read a single line from a file descriptor into the buffer
int read_line(int fd, char *buffer, size_t size) {
    ssize_t bytes_read = 0;
    char c;

    while (bytes_read < size - 1) {
        ssize_t result = read(fd, &c, 1);
        if (result <= 0) {
            break; // EOF or error
        }
        if (c == '\n') {
            if (bytes_read == 0) {
                continue; // Skip empty lines
            }
            break; // End of line
        }
        buffer[bytes_read++] = c;
    }
    buffer[bytes_read] = '\0'; // Null-terminate the buffer
    return bytes_read;
}

// Initialize the bank database with default capacity
int init_database(BankDatabase* db) {
    db->capacity = 10;
    db->count = 0;
    db->accounts = (BankAccountLog*)malloc(sizeof(BankAccountLog) * db->capacity);
    if (!db->accounts) {
        perror("Failed to allocate memory for database accounts");
        return -1;
    }
    for (int i = 0; i < db->capacity; i++) {
        memset(&db->accounts[i], 0, sizeof(BankAccountLog));
    }
    return 0;
}


// Free memory used by the bank database
void free_database(BankDatabase* db) {
    free(db->accounts);
    db->accounts = NULL;
    db->count = 0;
    db->capacity = 0;
}


// Find an account by bank ID
BankAccountLog* find_account(BankDatabase* db, const char* bank_id) {
    for (int i = 0; i < db->count; ++i) {
        if (strcmp(db->accounts[i].bank_id, bank_id) == 0) {
            return &db->accounts[i];
        }
    }
    return NULL;
}


// Ensure database has enough capacity, double if needed
int ensure_capacity(BankDatabase* db) {
    if (db->count >= db->capacity) {
        db->capacity *= 2;
        db->accounts = realloc(db->accounts, sizeof(BankAccountLog) * db->capacity);
        if (!db->accounts) {
            perror("Failed to reallocate memory for database accounts");
            return -1;
        }
        for (int i = db->count; i < db->capacity; i++) {
            memset(&db->accounts[i], 0, sizeof(BankAccountLog));
        }
    }
    return 0;
}

// Write the current database state into a log file
int write_log(BankDatabase* db, const char* log_path) {
    signal(SIGTERM, handle_termination);
    signal(SIGINT, handle_termination); // Set up signal handlers for making sure logging is more atomic

    int fd = open(log_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("Failed to open log file for writing");
        signal(SIGINT, handle_signal);
        signal(SIGTERM, handle_signal);
        return -1;
    }

    time_t now = time(NULL); // Get current time
    if (now == -1) {
        perror("Failed to get current time");
        close(fd);
        signal(SIGINT, handle_signal);
        signal(SIGTERM, handle_signal);
        return -1;
    }
    dprintf(fd, "# Adabank Log file updated @%s\n", ctime(&now));
    // Write each account's information to the log file
    for (int i = 0; i < db->count; ++i) {
        BankAccountLog* acc = &db->accounts[i];
        if (acc->is_closed) { // if account is closed, log it with a comment
            dprintf(fd, "# ");
        }
        dprintf(fd, "%s ", acc->bank_id);
        for (int j = 0; j < acc->op_count; ++j) {
            dprintf(fd, "%s ", acc->operations[j]);
        }
        dprintf(fd, "%d\n", acc->current_balance);
    }

    dprintf(fd, "\n## end of log.\n");

    if (close(fd) == -1) {
        perror("Failed to close log file after writing");
        signal(SIGINT, handle_signal);
        signal(SIGTERM, handle_signal);
        return -1;
    }

    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal); // Restore original signal handlers after writing
    return 0;
}

// Load a log file and reconstruct the database
int load_log(BankDatabase* db, const char* log_path) {
    if (init_database(db) != 0) {
        return -1;
    }
    int fd = open(log_path, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open log file for reading");
        return -1;
    }

    char line[1024];
    int is_first_line = 1;
    while (read_line(fd, line, sizeof(line)) > 0) { // Read each line from the log file
        if (is_first_line) {
            is_first_line = 0;
            continue;
        }

        if (strncmp(line, "## end of log.", 14) == 0) break;
        if (strlen(line) == 0) continue;

        char* ptr = line;

        if (*ptr == '#') { // Skip comments
            ptr++;
            while (*ptr && isspace((unsigned char)*ptr)) ptr++;
        }

        char id[MAX_BANK_ID_LEN];
        int id_len = 0;
        while (*ptr && !isspace((unsigned char)*ptr) && id_len < MAX_BANK_ID_LEN - 1) {
            id[id_len++] = *ptr++;
        }
        id[id_len] = '\0';

        if (id_len == 0) continue;

        while (*ptr && isspace((unsigned char)*ptr)) ptr++;

        BankAccountLog* acc = find_account(db, id);
        if (!acc) {
            if (ensure_capacity(db) != 0) {
                close(fd);
                return -1;
            }
            acc = &db->accounts[db->count++];
            strncpy(acc->bank_id, id, MAX_BANK_ID_LEN);
            acc->current_balance = 0;
            acc->op_count = 0;
        }

        while (*ptr) { // Process operations
            if (*ptr == 'D' || *ptr == 'W') {
                char op = *ptr++;
                while (*ptr && isspace((unsigned char)*ptr)) ptr++;

                char numbuf[16];
                int num_len = 0;
                while (*ptr && isdigit((unsigned char)*ptr) && num_len < sizeof(numbuf) - 1) {
                    numbuf[num_len++] = *ptr++;
                }
                numbuf[num_len] = '\0';

                if (num_len > 0) {
                    int amount = atoi(numbuf);
                    if (op == 'D') {
                        acc->current_balance += amount;
                        if (acc->op_count < MAX_TRANSACTIONS) {
                            snprintf(acc->operations[acc->op_count++], 8, "D %d", amount);
                        }
                    } else if (op == 'W') {
                        acc->current_balance -= amount;
                        if (acc->op_count < MAX_TRANSACTIONS) {
                            snprintf(acc->operations[acc->op_count++], 8, "W %d", amount);
                        }
                    }
                }

                while (*ptr && isspace((unsigned char)*ptr)) ptr++;
            }
            else if (isdigit((unsigned char)*ptr)) {
                char numbuf[16];
                int num_len = 0;
                while (*ptr && isdigit((unsigned char)*ptr) && num_len < sizeof(numbuf) - 1) {
                    numbuf[num_len++] = *ptr++;
                }
                numbuf[num_len] = '\0';

                if (num_len > 0) {
                    acc->current_balance = atoi(numbuf); // Update balance
                }
                break;
            }
            else {
                ptr++;
            }
        }
        if (acc->current_balance == 0) {
            acc->is_closed = 1;
        }
    }

    if (close(fd) == -1) { // Close the file descriptor
        perror("Failed to close log file after reading");
        return -1;
    }
    return 0;
}

