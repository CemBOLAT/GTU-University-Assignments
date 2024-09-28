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

void searchStudent(char **env)
{
	char *name = takeInput("Enter the name and surname of the student: ");
	name = cb_capitalize(name);
	pid_t pid;
	int save_stdout, save_stdin;
	int pipefd[2];
	if (name == NULL)
	{
		return;
	}
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
		char *path = pathFinder(env, "grep");
		if (path == NULL)
		{
			fprintf(stderr, "grep not found\n");
			cb_free(name);
			exit(1);
		}
		char *args[] = {path, name, "-w" , FILENAME, NULL};
		execve(args[0], args, env);
		exit(1);
	}
	else
	{
		close(pipefd[1]);
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
			fprintf(stderr, "No student found with the name %s\n", name);
			close(pipefd[0]);
		}
		else {
			char **lines = splitInput(infos, ",");
			printf("Name: %s\nGrade: %s", lines[0], lines[1]);
			cb_free2d((void **)lines);
			close(pipefd[0]);
		}
	}
	cb_free(name);
	dup2(save_stdout, STDOUT_FILENO);
	dup2(save_stdin, STDIN_FILENO);
}
