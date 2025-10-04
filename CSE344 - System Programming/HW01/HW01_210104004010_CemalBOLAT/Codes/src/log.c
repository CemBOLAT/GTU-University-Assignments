#include "../includes/funcs.h"
#include "../includes/errors.h"
#include "../includes/utils.h"

#include <sys/file.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int add_log(const char *macro, const char *content, const char *macro2, const char *error_str, int has_error) {
    const char *file_name = "log.txt";

    if (macro == NULL) {
        // No need to log this because it is control for the functions general flow
        write(STDERR_FILENO, "Log Macro Cannot be NULL!", strlen("Log Macro Cannot be NULL!"));
        return 1;
    }
    
    if (content == NULL) {
        // No need to log this because it is control for the functions general flow
        write(STDERR_FILENO, "Log Content Cannot be NULL!", strlen("Log Content Cannot be NULL!"));
        return 1;
    }

    if (macro2 == NULL) {
        // No need to log this because it is control for the functions general flow
        write(STDERR_FILENO, "Log Macro Cannot be NULL!", strlen("Log Macro Cannot be NULL!"));
        return 1;
    }
    if (has_error && error_str == NULL) {
        // No need to log this because it is control for the functions general flow
        write(STDERR_FILENO, "Log Error Cannot be NULL!", strlen("Log Error Cannot be NULL!"));
        return 1;
    }

    // Open the log file, if it does not exist, create it if it exists, append to it
    int fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (fd == -1) { // open error
        write(STDERR_FILENO, "Error: Cannot open log file!", strlen("Error: Cannot open log file!"));
        return 1;
    }

    time_t now;
    struct tm *time_info;
    char time_str[22]; // fixed size for time string "[YYYY-MM-DD HH:MM:SS]"

    if (time(&now) < 0){ // time() returns -1 on error
        my_perror("Error Cannot get time while logging: ");
        if (close(fd) == -1) {
            my_perror("Error Cannot close log file: ");
        }
        return 1;
    }

    time_info = localtime(&now);

    // strftime() returns 0 on error
    if (strftime(time_str, sizeof(time_str), "[%Y-%m-%d %H:%M:%S]", time_info) == 0) {
        // strftime is not a system call so it has no errno
        write(STDERR_FILENO, "Error: Cannot get time while logging!", strlen("Error: Cannot get time while logging!"));
        if (close(fd) == -1) {
            my_perror("Error Cannot close log file: ");
        }
        return 1;
    }    

    if (my_logger(fd, time_str, macro, content, macro2, error_str, has_error) == 1) {
        if (close(fd) == -1) {
            my_perror("Error Cannot close log file: ");
        }
        return 1;
    }
    if (close(fd) == -1) {
        my_perror("Error Cannot close log file: ");
        return 1;
    }

    return 0;
}