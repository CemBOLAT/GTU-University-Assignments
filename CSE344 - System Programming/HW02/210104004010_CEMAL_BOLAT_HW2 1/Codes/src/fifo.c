#include "fifo.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include "../includes/utils.h"
#include "../includes/daemon.h"
#include <errno.h>

int create_fifo(const char *fifo) {
    // If fifo exists unlink it first
    if (access(fifo, F_OK) != -1) { // FIFO exists
        if (unlink(fifo) == -1) {
            return -1;
        }
    } else if (errno != ENOENT) { // Error other than "no such file or directory"
        return -1;
    }
    errno = 0; // Reset errno before creating FIFO
    if (mkfifo(fifo, 0666) == -1) {
        return -1;
    }
    char create_msg[100];
    snprintf(create_msg, sizeof(create_msg), "FIFO %s created", fifo);
    return write_log(create_msg, 0);

}

int send_to_fifo(const char *fifo, int num1, int num2, int is_first) {
    int fd;
    do {
        fd = open(fifo, O_WRONLY);  // Add O_NONBLOCK to prevent blocking indefinitely
    } while (fd == -1 && errno == EINTR);

    if (fd == -1) {
        return -1;
    }

    // Write first number
    int check1 = 0;
    do {
        check1 = write(fd, &num1, sizeof(num1));
    } while (check1 == -1 && errno == EINTR);

    if (check1 == -1) {
        close(fd);
        return -1;
    }

    if (is_first) {
        do {
            check1 = write(fd, &num2, sizeof(num1));
        } while (check1 == -1 && errno == EINTR);
        
        if (check1 == -1) {
            close(fd);
            return -1;
        }
    }
    if (close(fd) == -1) {
        return -1;
    }
    char send_msg[100];
    if (is_first) {
        snprintf(send_msg, sizeof(send_msg), "Sent %d and %d to FIFO %s", num1, num2, fifo);
    } else {
        snprintf(send_msg, sizeof(send_msg), "Sent %d to FIFO %s", num1, fifo);
    }
    return write_log(send_msg, 0);
}

int receive_from_fifo(const char *fifo, int *values, int is_first) {
    int fd;
    do {
        // Wait for FIFO to be ready
        fd = open(fifo, O_RDONLY | O_NONBLOCK);
    } while (fd == -1 && errno == EINTR);

    if (fd == -1) {
        return -1;
    }
    // Read byte by byte
    int num;
    int i = 0;
    int num_to_read = is_first ? 2 : 1;
    do {
        int read_byte = read(fd, &num, sizeof(int));
        if (read_byte == -1) {
            if (errno == EAGAIN) {
                // FIFO is empty wait for a while and try again
                usleep(1000);
                errno = 0; // Reset errno before retrying
                continue;
            }
            if (errno == EINTR) {
                // Interrupted by a signal, retry
                continue;
            }
            int err = errno;
            if (close(fd) == -1) {
                errno = err;
                return -1;
            }
            return -1;
        }
        else if (read_byte == 0){
            continue; // No data read, continue looping timeout mechanism around
        }
        values[i] = num;
        i++; 
    } while (i < num_to_read);
    if (close(fd) == -1) {
        return -1;
    }
    char receive_msg[100];
    if (is_first) {snprintf(receive_msg, sizeof(receive_msg), "Received %d and %d from FIFO %s", values[0], values[1], fifo);} 
    else { snprintf(receive_msg, sizeof(receive_msg), "Received %d from FIFO %s", values[0], fifo);}
    return write_log(receive_msg, 0);
}