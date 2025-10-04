#include "../includes/utils.h"
#include "../includes/daemon.h"
#include "../includes/macros.h"
#include "../includes/fifo.h"
#include "../includes/child.h"
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int my_atoi(const char *str){
    int res = 0;
    int multiplier = 1;
    if (!str){
        errno = EINVAL;
        return -1;
    }
    if (str[0] == '-'){
        multiplier = -1;
        str++;
    }
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] < '0' || str[i] > '9'){
            errno = EINVAL;
            return -1;
        }
        res = res * 10 + str[i] - '0';
    }
    return res * multiplier;
}

void cleanup(void){
    
    if (access(FIFO1, F_OK) == 0){
        unlink(FIFO1);
    }
    else {
        if (errno != ENOENT){
            perror("access FIFO1");
        }
    }
    if (access(FIFO2, F_OK) == 0){
        unlink(FIFO2);
    }
    else {
        if (errno != ENOENT){
            perror("access FIFO2");
        }
    }
    // Log dosyasını kapat
    if (log_fd != 0){
        if (close(log_fd) == -1){
            perror("close log file");
        }
        log_fd = 0; // Reset log_fd to 0
    }

}