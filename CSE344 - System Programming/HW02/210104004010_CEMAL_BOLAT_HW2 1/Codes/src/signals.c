#include "../includes/signals.h"
#include "../includes/daemon.h"
#include "../includes/utils.h"
#include "../includes/macros.h"
#include "../includes/fifo.h"
#include "../includes/child.h"

#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int child_count = 0;

void handle_sigchld(int sig) {
    int status;
    pid_t pid;
    (void)sig; // Avoid unused parameter warning
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) // WHOHANG: return immediately if no child has exited
    {
        child_count += 1;
        char message[100];
        sprintf(message, "Child process %d terminated with status %d", pid, WEXITSTATUS(status));
        for (int i = 0; i < child_count_tracked; i++) {
            if (child_pids[i] == pid) {
                child_pids[i] = -1; // Mark as terminated
                break;
            }
        }
        write_log(message, 0);
    }
}

void handle_sigusr1(int sig) {
    (void)sig; // Avoid unused parameter warning

    if (daemon_pid == getpid()) {
        write_log("Received SIGUSR1 signal, reconfiguring daemon...", 0);
    } else {
        // Perform cleanup and exit child process
        cleanup();
        _exit(EXIT_SUCCESS);
    }

}

void handle_sigterm_and_signup(int sig) {
    // Perform cleanup and exit
    if (sig == SIGTERM) {
        if (daemon_pid == getpid()) {
            write_log("Received SIGTERM signal, terminating daemon...", 0);
        } else {
            char message[100];
            sprintf(message, "Received SIGTERM signal, terminating child process %d...", getpid());
            write_log(message, 0);
            cleanup();
            _exit(EXIT_SUCCESS);
        }
    } else if (sig == SIGHUP) {
        write_log("Received SIGHUP signal, terminating daemon...", 0);
    }
    for (int i = 0; i < child_count_tracked; i++) {
        if (child_pids[i] > 0) {
            if (kill(child_pids[i], SIGUSR1) == -1) {
                write_log("Sending SIGUSR1 to child that didn't terminate gracefully", 1);
                if (kill(child_pids[i], SIGKILL) == -1) {
                    write_log("Failed to kill child process", 1);
                } else {
                    write_log("Child process killed successfully", 0);
                }
            } else {
                child_pids[i] = -1; // Mark as terminated
            }
        }
    }

    int old_alarm = alarm(0);  // Cancel the previous alarm
    if (old_alarm == -1) {
        write_log("Failed to cancel alarm", 1);
        return; // Failure
    }
    sleep(5); // Wait for children to terminate

    write_log("All child processes terminated", 0);
    write_log("Daemon process terminated", 0);
    cleanup();

   
    _exit(EXIT_SUCCESS);
}

void alarm_handler(int sig) {
    (void)sig; // Avoid unused parameter warning
    write_log("Alarm signal received, checking for inactive children...", 0);
    if (check_inactive_children() == -1) {
        write_log("Error checking for inactive children", 1);
    }
    alarm(CHILD_ALARM); // Reset the alarm
}