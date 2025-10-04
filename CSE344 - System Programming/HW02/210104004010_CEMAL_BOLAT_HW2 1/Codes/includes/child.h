#ifndef CHILD_H

#define CHILD_H

#include <unistd.h>
#include <time.h>

extern pid_t child_pids[2]; // Array to store child process IDs
extern time_t child_last_active[2]; // Array to store last active time of child processes
extern int child_count_tracked; // Variable to track the number of child processes

#define CHILD_TIMEOUT 25 // Timeout duration in seconds for child processes
#define CHILD_ALARM 5 // Timeout duration in seconds for child processes

int     register_child(pid_t pid);
int     check_inactive_children(void);
void    setup_timeout_handler(void);


#endif
