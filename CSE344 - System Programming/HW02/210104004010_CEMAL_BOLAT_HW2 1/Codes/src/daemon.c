#include "../includes/daemon.h"
#include "../includes/signals.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>

// The daemon process should handle logging operations by storing process  execution details (e.g., start time, PID, termination status, and errors) in a log file.
int log_fd = 0;
pid_t daemon_pid = 0; // Variable to store the daemon process ID
int write_log(char *message, int is_error)
{
    time_t now;
    struct tm *tm_info;
    char timestamp[26];
    char log_entry[100];

    if (time(&now) == -1) {
        perror("time");
        return -1;
    }
    tm_info = localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // Format the log entry with proper size parameter
    if (is_error == 0) {
        snprintf(log_entry, sizeof(log_entry), "[%s] [%d] %s\n", timestamp, getpid(), message);
    } else {
        snprintf(log_entry, sizeof(log_entry), "[%s] [%d] %s: %s\n", timestamp, getpid(), message, strerror(errno));
    }

    int log_to_use = (log_fd == 0) ? STDERR_FILENO : log_fd;

    // Write the log entry

    int write_result;

    do {
        write_result = write(log_to_use, log_entry, strlen(log_entry));
    } while (write_result == -1 && errno == EINTR);

    if (write_result == -1) {
        perror("write log");
        return -1;
    }

    return 0;
}

int daemonize(void) {
    pid_t pid;
    int maxfd, fd;

    // Open log file // if exist clear it
    log_fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (log_fd == -1) {
        perror("Failed to open log file");
        return -1;
    }
  
    // Set up signal handlers
    signal(SIGUSR1, handle_sigusr1);
    signal(SIGTERM, handle_sigterm_and_signup);
    signal(SIGHUP, handle_sigterm_and_signup);
    
    // Log start of daemonization
    write_log("Starting daemonization process", 0);
    
    // First fork: detach from controlling terminal
    pid = fork();
    if (pid < 0) {
        write_log("First fork failed in daemonize()", 1);
        return -1;
    }
    if (pid > 0) {
        // Parent exits
        close(log_fd); // Close log file descriptor in parent
        exit(EXIT_SUCCESS);
    } else {
        // print exit status of the parent
        char buffer[100];
        // Get parent process ID & exit status
        snprintf(buffer, sizeof(buffer), "Parent process exited while creating daemon with status: 0 PID: %d", getppid());
        write_log(buffer, 0);
    }
    
    // Child continues: become session leader
    if (setsid() == -1) {
        write_log("setsid failed in daemonize()", 1);
        return -1;
    }

    
    // Second fork: prevent acquiring a controlling terminal
    pid = fork();
    if (pid < 0) {
        write_log("Second fork failed in daemonize()", 1);
        return -1;
    }
    if (pid > 0) {
        // First child exits
        close(log_fd); // Close log file descriptor in first child
        exit(EXIT_SUCCESS);
    }
    else {
        // print exit status of the first child
        char buffer[100];
        // Get first child process ID & exit status
        snprintf(buffer, sizeof(buffer), "First child exited while creating daemon with status: 0 PID: %d", getppid());
        write_log(buffer, 0);
    }
    // Final daemon process continues
    
    // Set file creation mask
    umask(0);
    
    // Change current directory to root
    if (chdir("/") == -1) {
        write_log("chdir failed in daemonize()", 1);
        return -1;
    }
    
    // Close all open file descriptors except log
    maxfd = sysconf(_SC_OPEN_MAX);
    if (maxfd == -1) {
        write_log("sysconf failed in daemonize()", 1);
        maxfd = 1024; // Fallback if sysconf fails
    }
    
    for (fd = 0; fd < maxfd; fd++) {
        if (fd != log_fd) {
            close(fd);
        }
    }
    
    // Open /dev/null for stdin, stdout, stderr
    fd = open("/dev/null", O_RDWR);
    if (fd == -1) {
        write_log("Failed to open /dev/null", 1);
        return -1;
    }
    
    // Setup stdin
    if (fd != STDIN_FILENO) {
        if (dup2(fd, STDIN_FILENO) != STDIN_FILENO) {
            write_log("Failed to redirect stdin to /dev/null", 1);
            return -1;
        }
    }
    
    // Redirect stdout to log file
    if (dup2(log_fd, STDOUT_FILENO) != STDOUT_FILENO) {
        write_log("Failed to redirect stdout to log file", 1);
        return -1;
    }

    // Redirect stderr to log file
    if (dup2(log_fd, STDERR_FILENO) != STDERR_FILENO) {
        write_log("Failed to redirect stderr to log file", 1);
        return -1;
    }
    
    // Close the original fd if it's not one of the standard ones
    if (fd > STDERR_FILENO) {
        close(fd);
    }
    
    // Log successful daemonization
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Successfully daemonized with second child PID: %d", getpid());
    daemon_pid = getpid();
    return write_log(buffer, 0);
}