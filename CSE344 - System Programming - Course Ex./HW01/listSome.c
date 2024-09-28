#include "util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

static bool isValidInput(char *input)
{
	for (size_t i = 0; i < strlen(input); i++)
	{
		if ((input[i] < '0' || input[i] > '9') && input[i] != ' ')
		{
			printf("<%c>\n", input[i]);
			return false;
		}
	}
	return true;
}

void listSome(char **envp)
{
	char *name = takeInput("Enter the number of entries to list and page number: ");
	if (name == NULL)
	{
		return;
	}
	if (isValidInput(name) == false || cb_nbrOfWords(name, " ") != 2)
	{
		fprintf(stderr, "Invalid input\n");
		cb_free(name);
		return;
	}
	pid_t pid;

	int save_stdout, save_stdin;
	int pipefd[2];
	pipe(pipefd);
	save_stdout = dup(STDOUT_FILENO);
	save_stdin = dup(STDIN_FILENO);
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr, "Fork failed\n");
		cb_free(name);
		exit(1);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		char *path = pathFinder(envp, "head");
		char **split = splitInput(name, " ");
		int arr[2] = {atoi(split[0]), atoi(split[1])};
		char *toStr = cb_itoa(arr[0] * arr[1]);
		if (toStr == NULL)
		{
			fprintf(stderr, "Memory allocation failed\n");
			cb_free2d((void **)split);
			exit(1);
		}
		cb_free2d((void **)split);
		if (path == NULL)
		{
			fprintf(stderr, "head not found\n");
			cb_free(name);
			exit(1);
		}
		char *args[] = {path, "-n", toStr, FILENAME, NULL};
		execve(args[0], args, envp);
		exit(1);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		waitpid(pid, NULL, 0);
		char infos[1000];
		size_t readBytes = read(pipefd[0], infos, 1000);
		if (readBytes < 0)
		{
			fprintf(stderr, "Error while reading from pipe\n");
			exit(1);
		}
		else if (readBytes == 0)
		{
			fprintf(stderr, "No data received from pipe\n");
			exit(1);
		}
		else
		{
			pid_t pid2;
			pid2 = fork();
			if (pid2 < 0)
			{
				fprintf(stderr, "Fork failed\n");
				cb_free(name);
				exit(1);
			}
			else if (pid2 == 0)
			{
				waitpid(pid, NULL, 0);
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				close(pipefd[1]);
				char *path = pathFinder(envp, "tail");
				if (path == NULL)
				{
					fprintf(stderr, "tail not found\n");
					cb_free(name);
					exit(1);
				}
				char **split = splitInput(name, " ");
				int arr[2] = {atoi(split[0]), atoi(split[1])};
				char *toStr = cb_itoa(arr[0]);
				cb_free2d((void **)split);
				char *args[] = {path, "-n", toStr, NULL};
				execve(args[0], args, envp);
				exit(1);
			}
			else
			{
				close(pipefd[1]);
				waitpid(pid2, NULL, 0);
			}
			infos[readBytes] = '\0';
			printf("%s", infos);
		}
	}
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stdin, STDIN_FILENO);
	close(pipefd[0]);
	cb_free(name);
}
