#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

int child_counter = 0;

void sigchld_handler(int signum)
{
	int status;
	pid_t pid;

	while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		printf("Child process %d terminated with exit status: %d\n", pid, WEXITSTATUS(status));
		child_counter--;
	}
}

void create_fifo(const char *fifo_name)
{
	if (mkfifo(fifo_name, 0666) == -1)
	{
		if (errno != EEXIST)
		{
			perror("Error creating FIFO");
			exit(EXIT_FAILURE);
		}
	}
}

pid_t save_fork(){
	pid_t pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return pid;
}

int save_open(const char *pathname, int flags){
	int fd = open(pathname, flags);
	if (fd == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	return fd;
}

int save_close(int fd){
	if (close(fd) == -1)
	{
		perror("close");
		exit(EXIT_FAILURE);
	}
	return 0;
}

int save_write(int fd, const void *buf, size_t count){
	if (write(fd, buf, count) == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
	return 0;
}

int save_sleep(unsigned int seconds){
	if (sleep(seconds) == -1)
	{
		perror("sleep");
		exit(EXIT_FAILURE);
	}
	return 0;
}

int save_printf(const char *format, ...){
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	return ret;
}



int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	signal(SIGCHLD, sigchld_handler);

	int num_children = 2;
	int num = atoi(argv[1]);
	if (num < 1)
	{
		fprintf(stderr, "Invalid argument: %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	int nums[num];
	srand(time(NULL));
	for (int i = 0; i < num; i++)
	{
		nums[i] = rand() % 10;
		printf("nums[%d]: %d\n", i, nums[i]);
	}

	create_fifo(FIFO1);
	create_fifo(FIFO2);

	pid_t pid;
	for (int i = 0; i < num_children; i++)
	{
		pid = save_fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				// Child Process 1: Summation
				int fd1 = save_open(FIFO1, O_RDONLY);
				int sum = 0;
				for (int j = 0; j < num; j++)
				{
					read(fd1, &nums[j], sizeof(int));
					sum += nums[j];
				}
				save_close(fd1);

				int fd2 = save_open(FIFO2, O_WRONLY);

				save_write(fd2, &sum, sizeof(int));
				save_close(fd2);
				exit(EXIT_SUCCESS);
			}
			else if (i == 1)
			{
				// Child Process 2: Multiplication

				int fd2 = save_open(FIFO2, O_RDONLY);
				int command;
				read(fd2, &command, sizeof(int));
				if (command == 1)
				{ // Assuming command value for multiplication is 1
					int result = 1;
					for (int j = 0; j < num; j++)
					{
						result *= nums[j];
					}
					printf("Result: %d\n", result);
				}
				else
				{
					printf("Child 2: Invalid command received\n");
				}
				save_close(fd2);
				exit(EXIT_SUCCESS);
			}
		}
	}

	// Parent Process
	save_sleep(10);

	int fd1 = save_open(FIFO1, O_WRONLY);
	save_write(fd1, &num, sizeof(int));
	save_close(fd1);

	int fd2 = save_open(FIFO2, O_RDONLY);

	int command = 1; // Command value for multiplication
	save_write(fd2, &command, sizeof(int));
	save_close(fd2);

	while (child_counter < num_children)
	{
		save_printf("Processing...\n");
		save_sleep(2);
	}

	save_printf("Parent process completed.\n");
	return 0;
}
