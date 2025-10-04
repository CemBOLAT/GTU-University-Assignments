#include "../includes/errors.h"
#include "../includes/utils.h"
#include "../includes/funcs.h"
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int create_file(const char *file_name) {
    if (string_check(file_name, ERR_FILE_NAME_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }

    int fd = open(file_name, O_CREAT | O_EXCL | O_WRONLY, 0644);
    if (fd == -1){
        if (errno == EEXIST) {
            // File already exists error
            add_log(ERR_FILE, file_name, ERR_CANNOT_CREATED, "File already exists", 1);
            my_write(STDERR_FILENO, ERR_FILE, file_name, ERR_ALREADY_EXISTS);
        }
        else {
            // Other errors
            add_log(ERR_FILE, file_name, ERR_CANNOT_CREATED, strerror(errno), 1);
            my_perror("Error happened while creating file: ");
        }
        return 1; // Error
    }
    else {
        // Creation successful, write the timestamp to the file 
        time_t now;
        // get the current time. time() is a system call that returns the current time
        if (time(&now) < 0) {
            // time() returns -1 on error
            add_log(ERR_FILE, file_name, ERR_CREATED_BUT_TIMESTAMP, strerror(errno), 1);
            my_perror("Error Cannot get time: ");
            // close() returns -1 on error
            if (close(fd) == -1) {
                my_perror("Error: ");
            }
            return 1;
        }

        // Time is successfully obtained, write it to the file
        if (write(fd, ctime(&now), strlen(ctime(&now))) == -1) {
            // write() returns -1 on error
            add_log(ERR_FILE, file_name, ERR_CREATED_BUT_TIMESTAMP, strerror(errno), 1);
            my_perror("Error: ");
            if (close(fd) == -1) {
                // close() returns -1 on error
                my_perror("Error: ");
            }
            return 1;
        }

        // Write successful, close the file
        if (close(fd) == -1) {
            // close() returns -1 on error
            add_log(ERR_FILE, file_name, ERR_CREATED_BUT_CLOSING, strerror(errno), 1);
            my_perror("Error: ");
            return 1;
        }
        // File created successfully log and write to stdout
        add_log(FILE, file_name, CREATED_SUCCESS, NULL, 0);
        // if writing to stdout fails, return 1 (error)
        return my_write(STDOUT_FILENO, FILE, file_name, CREATED_SUCCESS);
    }
    return 0;
}

int read_file(const char *file_name) {
    if (string_check(file_name, ERR_FILE_NAME_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }
    int fd = open(file_name, O_RDONLY);
    if (fd == -1) { // open error
        if (errno == ENOENT) { // file not found
            add_log(ERR_FILE, file_name, ERR_CANNOT_READ, "File not found", 1);
            my_write(STDERR_FILENO, ERR_FILE, file_name, ERR_NOT_FOUND);
        }
        else { // other errors
            add_log(ERR_FILE, file_name, ERR_CANNOT_READ, strerror(errno), 1);
            my_perror("Error: ");
        }
        return 1;
    }
    else {
        char buffer[1]; // read byte by byte
        ssize_t bytes_read;
        while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) { // read until EOF
            // write to stdout
            if (write(STDOUT_FILENO, buffer, bytes_read) == -1) {
                add_log(ERR_FILE, file_name, ERR_CANNOT_READ, strerror(errno), 1);
                my_perror("Error: ");
                // close the file
                if (close(fd) == -1) {
                    my_perror("Error: ");
                }
                return 1;
            }
        }
        if (bytes_read == -1) { // read error
            add_log(ERR_FILE, file_name, ERR_CANNOT_READ, strerror(errno), 1);
            my_perror("Error: ");
            if (close(fd) == -1) { // close error
                my_perror("Error: ");
            }
            return 1;
        }
        if (close(fd) == -1) { // close error
            add_log(ERR_FILE, file_name, ERR_CANNOT_READ, strerror(errno), 1);
            my_perror("Error: ");
            return 1;
        }
        // read successful log and write to stdout
        add_log(FILE, file_name, READ_SUCCESS, NULL, 0);
        // if writing to stdout fails, return 1 (error)
        return my_write(STDOUT_FILENO, FILE, file_name, READ_SUCCESS);
    }
    return 0;
}

int append_to_file(const char *file_name, const char *content) {

    if (string_check(file_name, ERR_FILE_NAME_NULL) == 1 ||
        string_check(content, ERR_FILE_CONTENT_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }

    int fd = open(file_name, O_WRONLY | O_APPEND);
    if (fd == -1) {
        if (errno == ENOENT) { // file not found
            add_log(ERR_FILE, file_name, ERR_NOT_FOUND, NULL, 0);
            my_write(STDERR_FILENO, ERR_FILE, file_name, ERR_NOT_FOUND);
        }
        else if (errno == EACCES) { // permission denied
            add_log(ERR_CANNOT_WRITE, file_name, ERR_FILE_LOCKED, NULL, 0);
            my_write(STDERR_FILENO, ERR_CANNOT_WRITE, file_name, ERR_FILE_LOCKED);
        }
        else { // other errors
            add_log(ERR_FILE, file_name, ERR_CANNOT_APPEND, strerror(errno), 1);
            my_perror("Error: ");
        }
        return 1;
    }
    else {
        // Lock the file
        if (flock(fd, LOCK_EX) == -1) {
            add_log(ERR_FILE, file_name, ERR_CANNOT_APPEND, strerror(errno), 1);
            my_perror("Error: ");
            // Close the file
            if (close(fd) == -1) {
                my_perror("Error: ");
            }
            return 1;
        }

        if (write(fd, content, strlen(content)) == -1 || write(fd, "\n", 1) == -1) {
            add_log(ERR_FILE, file_name, ERR_CANNOT_APPEND, strerror(errno), 1);
            my_perror("Error: ");
            // Unlock the file
            if (flock(fd, LOCK_UN) == -1) {
                my_perror("Error: ");
            }
            // Close the file
            if (close(fd) == -1) {
                my_perror("Error: ");
            }
            return 1;
        }

        // Write successful, unlock the file
        if (flock(fd, LOCK_UN) == -1) {
            add_log(ERR_FILE, file_name, ERR_CANNOT_APPEND, strerror(errno), 1);
            my_perror("Error");
            // Close the file
            if (close(fd) == -1) {
                my_perror("Error");
            }
            return 1;
        }

        // Close the file
        if (close(fd) == -1) {
            add_log(ERR_FILE, file_name, ERR_CANNOT_APPEND, strerror(errno), 1);
            my_perror("Error");
            return 1;
        }
        // Append successful log and write to stdout
        add_log(FILE, file_name, "\" appended successfully.", NULL, 0);
        // if writing to stdout fails, return 1 (error)
        return my_write(STDOUT_FILENO, FILE, file_name, "\" appended successfully.\n");
    }
    return 0;
}

int delete_file(const char *filename){
    if (string_check(filename, ERR_FILE_NAME_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }

    pid_t pid = fork();

    if (pid == -1) { // fork error
        add_log(ERR_FILE, filename, ERR_CANNOT_DELETE, strerror(errno), 1);
        my_perror("Error forking process");
        return 1;
    }
    else if (pid == 0) {
        if (unlink(filename) == -1) { // unlink error
            _exit(errno);
        }
        _exit(EXIT_SUCCESS);
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) { // waitpid error
            add_log(ERR_FILE, filename, ERR_CANNOT_DELETE, strerror(errno), 1);
            my_perror("Error waiting for child process");
            return 1;
        } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            errno = WEXITSTATUS(status); // set errno to the child's exit status
            if (errno == ENOENT) { // file not found
                add_log(ERR_FILE, filename, ERR_NOT_FOUND, NULL, 0);
                my_write(STDERR_FILENO, ERR_FILE, filename, ERR_NOT_FOUND);
            }
            else {
                add_log(ERR_FILE, filename, ERR_CANNOT_DELETE, strerror(errno), 1);
                my_perror("Error on deleting file: ");
            }
            return 1;
        } else { // deletion successful
            // Deletion successful log and write to stdout
            add_log(FILE, filename, DELETED_SUCCESS, NULL, 0);
            // if writing to stdout fails, return 1 (error)
            return my_write(STDOUT_FILENO, FILE, filename, DELETED_SUCCESS);
        }
    }
    return 0;
}