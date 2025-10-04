#ifndef UTILS_H

#define UTILS_H

#include <stdio.h>
#include <sys/stat.h>

#define RED_COLOR "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define RESET_COLOR "\033[0m"
#define BLUE_COLOR "\033[0;34m"
#define YELLOW_COLOR "\033[0;33m"

int my_atoi(const char *str);
int get_port(const char *port);
void cleanup_resources();
int file_check_while_sending(const char *filename, int fd, struct stat *file_stat);
void enter_with_valid_username(char *username);
void safe_printf(const char *format, ...);

#endif
