#ifndef DAEMON_H

#define DAEMON_H

#include <unistd.h>

#define LOG_FILE "/tmp/daemon.log"

int daemonize();
int write_log(char *message, int is_error);

extern int log_fd;
extern pid_t daemon_pid; // Variable to store the daemon process ID

#endif
