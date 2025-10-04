#include "../includes/errors.h"
#include "../includes/funcs.h"
#include "../includes/utils.h"

#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int create_dir(const char *dir_name) {
    if (string_check(dir_name, ERR_DIR_NAME_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }
    if (mkdir(dir_name, 0777) == -1) {
        if (errno == EEXIST) {
            // Directory already exists error
            add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_CREATED, "Directory already exists", 1);
            my_write(STDERR_FILENO, ERR_DIRECTORY, dir_name, ERR_ALREADY_EXISTS);
        }
        else {
            // Other errors
            add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_CREATED, strerror(errno), 1);
            my_perror("Error happened while creating directory: ");
        }
        return 1; // Error
    }
    else {
        // Directory created successfully log and write to stdout
        add_log(DIRECTORY, dir_name, CREATED_SUCCESS, NULL, 0);
        // if writing to stdout fails, return 1 (error)
        return my_write(STDOUT_FILENO, DIRECTORY, dir_name, CREATED_SUCCESS);
    }
    return 0; // Success
}

int list_dir(const char *dir_name){

    if (string_check(dir_name, ERR_DIR_NAME_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }

    pid_t pid = fork(); 
    if (pid == -1) {
        // Error forking process
        add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, strerror(errno), 1);
        my_perror("Error forking process: ");
        return 1;
    }
    else if (pid == 0) {
        // Check if the directory exists
        if (access(dir_name, F_OK) == -1) {
            _exit(errno);
        }
        // Open the directory
        DIR *dir = opendir(dir_name);
        if (dir == NULL) {
            _exit(errno);
        }
        
        // Read the directory and list all files
        struct dirent *entry;
        while ((entry = readdir(dir)) != NULL) {
            // List all files in the directory ignore . and .. (current and parent directory)
            if (strcmp(entry->d_name, ".") == 0 || 
                strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            // Write the file name to the stdout
            if (write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name)) == -1) {
                int write_errno = errno;
                // Close the directory before exiting
                // No need to check the return value of closedir because
                //      we are exiting with the error code from write()
                closedir(dir); 
                _exit(write_errno);
            }
            if (write(STDOUT_FILENO, "\n", 1) == -1) {
                int write_errno = errno;
                // Close the directory before exiting
                // No need to check the return value of closedir because 
                //      we are exiting with the error code from write()
                closedir(dir);
                _exit(write_errno);
            }
        }
        // Close the directory
        if (closedir(dir) == -1) {
            _exit(errno);
        }
        // Exit the child process
        _exit(EXIT_SUCCESS);
    }
    else {
        int status;

        if (waitpid(pid, &status, 0) == -1) {
            // Error waiting for child process
            add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, strerror(errno), 1);
            my_perror("Error waiting for child process");
            return 1;
        } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) { // Child process exited with an error
            // Set errno to the exit status of the child process
            errno = WEXITSTATUS(status);
            if (errno == ENOENT) { // Directory not found
                add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, "Directory not found", 1);
                my_write(STDERR_FILENO, DIRECTORY, dir_name, ERR_NOT_FOUND);
            }
            else { // Other errors
                add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, strerror(errno), 1);
                my_perror("Error on listing directory: ");
            }
            return 1; // Error
        }
        else { // Child process exited successfully
            // Log and write to stdout
            add_log(DIRECTORY, dir_name, LISTED_SUCCESS, NULL, 0);
            // if writing to stdout fails, return 1 (error)
            return my_write(STDOUT_FILENO, DIRECTORY, dir_name, LISTED_SUCCESS);
        }
    }
    return 0;
}

int list_files_by_extension(const char *dir_name, const char *extension) {

    if (string_check(dir_name, ERR_DIR_NAME_NULL) == 1 ||
        string_check(extension, ERR_EXTENSION_NULL) == 1) {
        // No need to log this because it is control for the functions general flow
        return 1;
    }
    
    pid_t pid = fork();
    if (pid == -1) {
        // Error forking process
        add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, strerror(errno), 1);
        my_perror("Error forking process");
        return 1;
    }
    else if (pid == 0) {
        // Check if the directory exists
        if (access(dir_name, F_OK) == -1) {
            _exit(errno);
        }
        // Open the directory
        DIR *dir = opendir(dir_name);
        if (dir == NULL) {
            _exit(errno);
        }
        struct dirent   *entry;
        int             number_of_files = 0;
        while ((entry = readdir(dir)) != NULL) {
            // List all files in the directory ignore . and ..
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            // Check if the file has the given extension
            char *file_extension = strrchr(entry->d_name, '.'); // Find the last occurrence of '.'
            if (file_extension != NULL && strcmp(file_extension, extension) == 0) { // If the extension is the same
                number_of_files++; // Increment the number of files
                // Write the file name to the stdout
                if (write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name)) == -1) {
                    int write_errno = errno;
                    // Close the directory before exiting
                    // No need to check the return value of closedir because we are exiting with the error code from write()
                    closedir(dir);
                    _exit(write_errno);
                }
                if (write(STDOUT_FILENO, "\n", 1) == -1) {
                    int write_errno = errno;
                    // Close the directory before exiting
                    // No need to check the return value of closedir because we are exiting with the error code from write()
                    closedir(dir);
                    _exit(write_errno);
                }
            }
        }
        // Close the directory
        if (closedir(dir) == -1) { _exit(errno); }
        // If no files found with the given extension, exit with status 255 (arbitrary value)
        if (number_of_files == 0) { _exit(255);}
        exit(EXIT_SUCCESS);
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) { // Wait for the child process
            add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, strerror(errno), 1);
            my_perror("Error waiting for child process");
            return 1;
        } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            errno = WEXITSTATUS(status); // Set errno to the exit status of the child process
            if (errno == ENOENT) { // Directory not found
                add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, "Directory not found", 1);
                my_write(STDERR_FILENO, DIRECTORY, dir_name, ERR_NOT_FOUND);
            }
            else if (errno == 255) { // No files found with the given extension
                add_log("No files with extension \"", extension, "\" found in", dir_name, 1);
                if (write(STDERR_FILENO, "No files with extension \"", strlen("No files with extension \"")) == -1) {
                    return 1;
                }
                if (write(STDERR_FILENO, extension, strlen(extension)) == -1) {
                    return 1;
                }
                if (write(STDERR_FILENO, "\" found in directory \"", strlen("\" found in directory ")) == -1) {
                    return 1;
                }
                if (write(STDERR_FILENO, dir_name, strlen(dir_name)) == -1) {
                    return 1;
                }
                if (write(STDERR_FILENO, "\n", 2) == -1) {
                    return 1;
                }
                return 0;
            }
            else { // Other errors
                add_log(DIRECTORY, dir_name, ERR_CANNOT_LIST, strerror(errno), 1);
                my_perror("Error on listing directory: ");
            }
            return 1;
        }
        else { // Child process exited successfully
            // Log and write to stdout
            add_log(DIRECTORY, dir_name, LISTED_SUCCESS, NULL, 0);
            // if writing to stdout fails, return 1 (error)
            return my_write(STDOUT_FILENO, DIRECTORY, dir_name, LISTED_SUCCESS);
        }
    }
    return 0;
}

int delete_dir(const char *dir_name) {

    if (string_check(dir_name, ERR_DIR_NAME_NULL) == 1) {
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        // Error forking process
        add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_DELETE, strerror(errno), 1);
        my_perror("Error forking process");
        return 1;
    }
    else if (pid == 0) {
        if (rmdir(dir_name) == -1) {
            // Error deleting directory
            _exit(errno);
        }
        else {
            _exit(EXIT_SUCCESS);
        }
    }
    else {
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            // Error waiting for child process
            add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_DELETE, strerror(errno), 1);
            my_perror("Error waiting for child process");
            return 1;
        } else if (WIFEXITED(status) && WEXITSTATUS(status) != 0) {
            // Child process exited with an error
            errno = WEXITSTATUS(status);
            if (errno == ENOENT) {
                // Directory not found
                add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_DELETE, "Directory not found", 1);
                my_write(STDERR_FILENO, ERR_DIRECTORY, dir_name, ERR_NOT_FOUND);
            }
            else if (errno == ENOTEMPTY) {
                add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_DELETE,  "Directory is not empty", 1);
                my_write(STDERR_FILENO, ERR_DIRECTORY, dir_name, "\" is not empty.\n");
            }
            else { // Other errors
                add_log(ERR_DIRECTORY, dir_name, ERR_CANNOT_DELETE, strerror(errno), 1);
                my_perror("Error on deleting directory: ");
            }
            return 1; // Error
        }
        else { // Child process exited successfully
            // Log and write to stdout
            add_log(DIRECTORY, dir_name, DELETED_SUCCESS, NULL, 0);
            // if writing to stdout fails, return 1 (error)
            return my_write(STDOUT_FILENO, DIRECTORY, dir_name, DELETED_SUCCESS);
        }
    }
    return 0;
}