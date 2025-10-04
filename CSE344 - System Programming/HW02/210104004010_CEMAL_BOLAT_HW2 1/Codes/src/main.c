/*
Implement a communication protocol between two processes using IPC and introduce 
a daemon process to handle background operations. Follow these steps:

Initial Setup:

• The program should take two integer arguments from the command line. 
• Define an integer variable named “result”. Assign its value as zero and perform 
the following steps sequentially.
*/

#include "../includes/macros.h"
#include "../includes/utils.h"
#include "../includes/fifo.h"
#include "../includes/daemon.h"
#include "../includes/child.h"
#include "../includes/signals.h"
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int result = 0;
    int num1, num2;
    if (argc != 3) {
        dprintf(STDERR_FILENO, USAGE, argv[0]);
        return 1;
    }
    if ((num1 = my_atoi(argv[1])) && errno == EINVAL) {
        perror("Invalid number type on first argument");
        return 1;
    }
    if ((num2 = my_atoi(argv[2])) && errno == EINVAL) {
        perror("Invalid number type on second argument");
        return 1;
    }
    
    if (daemonize() == -1) {
        // no errno set
        if (errno == 0) {
            perror("Daemonize failed");
        }
        return 1;
    }

    setup_timeout_handler();
    
    if (create_fifo(FIFO1) == -1) {
        write_log("Error creating FIFO1", 1);
        return 1;
    }
    if (create_fifo(FIFO2) == -1) {
        write_log("Error creating FIFO2", 1);
        unlink(FIFO1);
        return 1;
    }
    
    signal(SIGCHLD, handle_sigchld);
    
    pid_t pid1, pid2;

    if ((pid1 = fork()) == -1) {
        write_log("Error forking first child", 1);
        cleanup();
        return 1;
    }
    else if (pid1 == 0){
        sleep(10);
        int values[2] = {0, 0};
        if (receive_from_fifo(FIFO1, values, 1) == -1) {
            write_log("Error receiving from FIFO1", 1);
            cleanup();
            _exit(EXIT_FAILURE);
        }
        result = values[0] > values[1] ? values[0] : values[1];
        if (send_to_fifo(FIFO2, result, 0, 0) == -1) {
            write_log("Error sending to FIFO2", 1);
            cleanup();
            _exit(EXIT_FAILURE);
        }
        cleanup();
        _exit(EXIT_SUCCESS);
    }
    else {
        if (register_child(pid1) == -1) {
            write_log("Error registering first child", 1);
            cleanup();
            _exit(EXIT_FAILURE);
        }
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Daemon process %d created child process %d", getpid(), pid1);
        if (write_log(buffer, 0) == -1) {
            perror("Error writing log");
            cleanup();
            _exit(EXIT_FAILURE);
        }
        if (send_to_fifo(FIFO1, num1, num2, 1) == -1) {
            write_log("Error sending to FIFO1", 1);
            cleanup();
            _exit(EXIT_FAILURE);
        }
    }

    if ((pid2 = fork()) == -1) {
        write_log("Error forking second child", 1);
        cleanup();
        return 1;
    }
    else if (pid2 == 0) {
        sleep(10);
        int largest = 0;
        if (receive_from_fifo(FIFO2, &largest, 0) == -1) {
            write_log("Error receiving from FIFO2", 1);
            cleanup();
            _exit(EXIT_FAILURE);
        }
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Largest number is %d", largest);
        if (write_log(buffer, 0) == -1) {
            cleanup();
            _exit(EXIT_FAILURE);
        }
        cleanup();
        _exit(EXIT_SUCCESS);
    }
    else {
        if (register_child(pid2) == -1) {
            write_log("Error registering second child", 1);
            cleanup();
            _exit(EXIT_FAILURE);
        }
        char buffer[100];
        snprintf(buffer, sizeof(buffer), "Daemon process %d created child process %d", getpid(), pid2);
        if (write_log(buffer, 0) == -1) {
            perror("Error writing log");
            cleanup();
            _exit(EXIT_FAILURE);
        }
        while (child_count < 2){
            write_log("Proceeding...", 0);

            sleep(2); // Sleep for 2 seconds
        }
        cleanup();
        
        char buffer1[100];
        snprintf(buffer1, sizeof(buffer1), "Daemon process %d terminated with status 0", getpid());
        if (write_log(buffer1, 0) == -1) {
            perror("Error writing log");
        }
        _exit(EXIT_SUCCESS);
    }
    return 0;
}