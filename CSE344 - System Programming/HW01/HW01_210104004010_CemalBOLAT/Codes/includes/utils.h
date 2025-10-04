#ifndef UTILS_H
#define UTILS_H

int string_check(const char *str, const char *error_message);
int my_write(int fd, const void *buffer1, const void *middle, const void *buffer2);
int my_perror(const char *error_message);
int my_logger(int fd, const char *timestr, const char *macro, const char *content, const char *macro2, const char *error_str, int has_error);

#endif // UTILS_H