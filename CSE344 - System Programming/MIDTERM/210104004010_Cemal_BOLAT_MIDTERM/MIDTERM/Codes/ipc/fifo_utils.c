#include "./include/fifo_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

// Create a FIFO; remove it first if it already exists
int create_fifo(const char* fifo_name) {
    if (access(fifo_name, F_OK) == 0) {
        if (unlink(fifo_name) == -1) {
            perror("unlink");
            return -1;
        }
    }
    if (mkfifo(fifo_name, 0666) == -1) {
        if (errno != EEXIST) {
            perror("mkfifo");
            return -1;
        }
    }
    return 0;
}

// Remove a FIFO
int remove_fifo(const char* fifo_name) {
    if (unlink(fifo_name) == -1) {
        perror("unlink");
        return -1;
    }
    return 0;
}

// Open a FIFO for writing
int open_fifo_write(const char* fifo_name) {
    int fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        return -1;
    }
    return fd;
}

// Open a FIFO for reading
int open_fifo_read(const char* fifo_name) {
    int fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("open_fifo_read");
    }
    return fd;
}

// Generate a client FIFO name based on the process PID
void generate_client_fifo_name(char* buffer, pid_t pid) {
    snprintf(buffer, 64, "./ClientFIFO_CemalBOLAT%d", pid);
}
