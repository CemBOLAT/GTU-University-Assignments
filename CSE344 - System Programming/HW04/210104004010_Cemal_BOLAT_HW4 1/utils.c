// utils.c
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

int my_atoi(const char *str){
    int result = 0;
    while (*str) {
        if (*str < '0' || *str > '9') {
            errno = EINVAL; // Geçersiz karakter hatası
            return -1; // Hata durumu
        }
        result = result * 10 + (*str - '0');
        str++;
    }
    return result;
}

int my_readline(int fd, char *buf, size_t size) {
    // Read char by char until newline or EOF

    size_t i = 0;
    while (i < size - 1) {
        ssize_t n = read(fd, &buf[i], 1);
        if (n < 0) {
            perror("Error reading from file");
            return -1; // Hata durumu
        }
        else if (n == 0) {
            break; // EOF or error
        }
        else if (buf[i] == '\n') {
            i++;
            break;
        }
        i++;
    }
    buf[i] = '\0'; // Null-terminate the string
    return i; // Return the number of bytes read
}