#ifndef UTILS_H

#define UTILS_H

#include <stddef.h>

int     my_atoi(const char *str);
int     get_port(const char *port);
int     reconfigure_server(int port);
void    trim_the_newline(char *str);
void    log_to_file(const char *msg);
void    init_log_file(const char *filename);
int     is_username_taken(const char *username);
void    cleanup_resources(void);
void    init_username(char *usr, int client_fd);
void    print_proper_server_prompt(const char *username, char *buffer);
void safe_printf(const char *format, ...);

#endif
