#include "../include/teller_api.h"
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

// Create a teller process and run the given function
pid_t Teller(void* (*func)(void*), void* arg) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Teller: fork failed");
        return -1;
    }
    if (pid == 0) {
        // Child process: call the function and exit
        func(arg);
        exit(EXIT_SUCCESS);
    } else {
        free(arg); // Parent process: free the argument
    }

    // Parent returns the child's PID
    return pid;
}

// Wait for a teller process to terminate
int waitTeller(pid_t pid, int* status) {
    return waitpid(pid, status, 0);
}
