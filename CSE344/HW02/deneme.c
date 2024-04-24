#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
	int i = 5;
	struct sigaction sa;
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGCHLD, &sa, NULL) == -1)
	{
		perror("sigaction");
		exit(EXIT_FAILURE);
	}

	int array[i];
	int array2[i];
	for (int j = 0; j < i; j++)
	{
		array[j] = rand() % 10;
	}

	// Create two FIFOs
	if (mkfifo("fifo1", 0666) == -1)
	{
		perror("mkfifo");
		exit(EXIT_FAILURE);
	}

	// Fork a child process
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0) // Child process for writing
	{
		int fd1 = open("fifo1", O_WRONLY);
		if (fd1 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (write(fd1, array, sizeof(array)) == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		close(fd1);
		exit(EXIT_SUCCESS);
	}
	else // Parent process for reading
	{
		int fd1 = open("fifo1", O_RDONLY);
		if (fd1 == -1)
		{
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (read(fd1, array2, sizeof(array)) == -1)
		{
			perror("read");
			exit(EXIT_FAILURE);
		}
		close(fd1);
		wait(NULL); // Wait for the child process to finish
		for (int j = 0; j < i; j++)
		{
			printf("%d ", array2[j]);
		}
		printf("\n");
	}
	//delete fifos
	unlink("fifo1");


	return 0;
}
