#ifndef FIFO_UTILS_H
#define FIFO_UTILS_H

#include <sys/types.h>

// Create a FIFO with the given name
int create_fifo(const char* fifo_name);

// Remove (unlink) a FIFO
int remove_fifo(const char* fifo_name);

// Open a FIFO for writing
int open_fifo_write(const char* fifo_name);

// Open a FIFO for reading
int open_fifo_read(const char* fifo_name);

// Generate a client FIFO name based on the process PID (e.g., ClientFIFO_1234)
void generate_client_fifo_name(char* buffer, pid_t pid);

#endif // FIFO_UTILS_H
