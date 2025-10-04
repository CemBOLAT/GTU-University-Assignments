#ifndef SIGNALS_H
#define SIGNALS_H

void handle_sigchld(int sig);
void handle_sigusr1(int sig);
void handle_sigterm_and_signup(int sig);
void alarm_handler(int sig);

extern int child_count;

#endif
