#include "../includes/child.h"
#include "../includes/signals.h"
#include "../includes/daemon.h"
#include "../includes/utils.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

int child_pids[2]; // Array to store child process IDs
time_t child_last_active[2]; // Array to store last active time of child processes
int child_count_tracked = 0; // Variable to track the number of child processes

int register_child(pid_t pid){
    if (child_count_tracked < 2){
        child_pids[child_count_tracked] = pid;
        time_t now = time(NULL);
        if (now == -1) {
            write_log("Failed to get current time", 1);
            return -1; // Failure
        }
        child_last_active[child_count_tracked] = now;
        child_count_tracked++;    
        return 0; // Success
    } else {
        write_log("Maximum number of child processes reached", 1);
        return -1; // Failure
    }
}

int check_inactive_children(){
    time_t now = time(NULL);
    int inactive_count = 0;
    if (now == -1) {
        write_log("Failed to get current time", 1);
        return -1; // Failure
    }
    for (int i = 0; i < child_count_tracked; i++){
        if (child_pids[i] != 0 && child_pids[i] != -1 && difftime(now, child_last_active[i]) > CHILD_TIMEOUT){
            char message[100];
            snprintf(message, sizeof(message), "Child process %d has been inactive for too long", child_pids[i]);
            if (write_log(message, 0) == -1) {
                return -1; // Failure
            }          
            inactive_count++;
        }
    }
    if (inactive_count != 0){
        // Kill all child processes..
        for (int i = 0; i < child_count_tracked; i++){
            if (child_pids[i] != 0 && child_pids[i] != -1){
                if (kill(child_pids[i], SIGUSR1) == -1){
                    if (errno == ESRCH){ // No such process
                        continue; // Process already terminated
                    } else {
                        // Error occurred while trying to kill the process
                        char error_message[100];
                        snprintf(error_message, sizeof(error_message), "Failed to terminate child process %d", child_pids[i]);
                        if (write_log(error_message, 1) == -1) {
                            return -1; // Failure
                        }
                    } 
                }
            }
        }

        int old_alarm = alarm(0);  // Cancel the previous alarm
        if (old_alarm == -1) {
            write_log("Failed to cancel alarm", 1);
            return -1; // Failure
        }
        sleep(5); // Wait for 5 seconds before checking again
        char buffer1[100];
        snprintf(buffer1, sizeof(buffer1), "Daemon process %d terminated with status 0", getpid());
        if (write_log(buffer1, 0) == -1) {
            perror("Error writing log");
        }
        _exit(EXIT_FAILURE); // Exit the daemon process
    }
    return 0; // Success
}

void setup_timeout_handler(){
    if (getpid() == daemon_pid){
        child_count_tracked = 0; // Reset child count
        for (int i = 0; i < 2; i++){
            child_pids[i] = 0; // Initialize child PIDs to 0
            child_last_active[i] = 0; // Initialize child start times to 0
        }
        // Set up a signal handler for SIGALRM
        signal(SIGALRM, alarm_handler);
        alarm(CHILD_ALARM); // Set the alarm for the timeout duration
    }
}