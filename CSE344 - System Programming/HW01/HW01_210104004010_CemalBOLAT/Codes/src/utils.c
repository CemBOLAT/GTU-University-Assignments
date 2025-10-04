#include "../includes/utils.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int string_check(const char *str, const char *error_message) {
    if (str == NULL) {
        write(STDERR_FILENO, error_message, strlen(error_message));
        return 1;
    }
    return 0;
}

int my_write(int fd, const void *buffer1, const void *middle, const void *buffer2) {
    if (write(fd, buffer1, strlen(buffer1)) < 0) {
        if (fd != STDERR_FILENO) {
            my_perror("Error: System Call Interrupted while writing");
        }
        return 1;
    }
    if (write(fd, middle, strlen(middle)) < 0) {
        if (fd != STDERR_FILENO) {
            my_perror("Error: System Call Interrupted while writing");
        }
        return 1;
    }
    if (write(fd, buffer2, strlen(buffer2)) < 0) {
        if (fd != STDERR_FILENO) {
            my_perror("Error: System Call Interrupted while writing");
        }
        return 1;
    }
    return 0;
}

int my_perror(const char *error_message) {
    int errorCode = errno;
    const char *errnoMessage = strerror(errorCode);
    if (write(STDERR_FILENO, error_message, strlen(error_message)) < 0) {
        return 1;
    }
    if (write(STDERR_FILENO, errnoMessage, strlen(errnoMessage)) < 0) {
        return 1;
    }
    if (write(STDERR_FILENO, "\n", 1) < 0) {
        return 1;
    }
    return 0;
}

int my_logger(int fd, const char *timestr, const char *macro, const char *content, const char *macro2, const char *error, int has_error) {
    // write the log to the file descriptor and return 1 if there is an error
    if (write(fd, timestr, strlen(timestr)) < 0) {
        my_perror("Error: System Call Interrupted while writing to log file");
        return 1;
    }
    if (write(fd, " ", 1) < 0) {
        my_perror("Error: System Call Interrupted while writing to log file");
        return 1;
    }
    if (write(fd, macro, strlen(macro)) < 0) {
        my_perror("Error: System Call Interrupted while writing to log file");
        return 1;
    }
    if (write(fd, content, strlen(content)) < 0) {
        my_perror("Error: System Call Interrupted while writing to log file");
        return 1;
    }
    if (write(fd, macro2, strlen(macro2)) < 0) {
        my_perror("Error: System Call Interrupted while writing to log file");
        return 1;
    }
    if (has_error) {
        if (write(fd, " ", 1) < 0) {
            my_perror("Error: System Call Interrupted while writing to log file");
            return 1;
        }
        if (write(fd, error, strlen(error)) < 0) {
            my_perror("Error: System Call Interrupted while writing to log file");
            return 1;
        }
        if (write(fd, "\n", 1) < 0) {
            my_perror("Error: System Call Interrupted while writing to log file");
            return 1;
        }
    }
    else {
        if (macro2[strlen(macro2) - 1] != '\n') { // if the last character is not a newline add a newline
            if (write(fd, "\n", 1) < 0) {
                my_perror("Error: System Call Interrupted while writing to log file");
                return 1;
            }
        }
    }
    
    return 0;
}