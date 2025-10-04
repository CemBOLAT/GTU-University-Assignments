#include "./include/shm_utils.h"
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Create or open a shared memory segment
// create = 1: create a new shared memory, 0: open existing
SharedMemoryData* create_shared_memory(const char* shm_name, int create) {
    int shm_fd;
    if (create) {
        shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("shm_open create");
            return NULL;
        }
        if (ftruncate(shm_fd, SHM_SIZE) == -1) {
            perror("ftruncate");
            close(shm_fd);
            return NULL;
        }
    } else {
        shm_fd = shm_open(shm_name, O_RDWR, 0666);
        if (shm_fd == -1) {
            perror("shm_open open");
            return NULL;
        }
    }

    // Map shared memory into process address space
    void* ptr = mmap(0, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        return NULL;
    }

    return (SharedMemoryData*)ptr;
}

// Destroy shared memory segment
// If is_child = 1, only unmap memory; otherwise unlink shared memory
void destroy_shared_memory(const char* shm_name, SharedMemoryData* shm_ptr, int is_child) {
    if (shm_ptr) {
        if (is_child) {
            munmap(shm_ptr, SHM_SIZE);
        } else {
            shm_unlink(shm_name);
        }
    }
}
