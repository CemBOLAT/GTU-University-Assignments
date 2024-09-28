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

void showAll(char **envp){
	pid_t pid;
	int save_stdout, save_stdin;
	int pipefd[2];
	pipe(pipefd);
	save_stdout = dup(STDOUT_FILENO);
	save_stdin = dup(STDIN_FILENO);
	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Fork failed\n");
		exit(1);
	}
	else if (pid == 0){
		close(pipefd[0]);
		dup2(pipefd[1], 1);
		close(pipefd[1]);
		char *path = pathFinder(envp, "cat");
		if (path == NULL){
			fprintf(stderr, "cat not found\n");
			exit(1);
		}
		char *args[] = {path, FILENAME, NULL};
		execve(args[0], args, envp);
		exit(1);
	}
	else{
		close(pipefd[1]);
		waitpid(pid, NULL, 0);
		char infos[1000];
		if (read(pipefd[0], infos, 1000) == 0){
			fprintf(stderr, "Error while reading from pipe\n");
			exit(1);
		}
		close(pipefd[0]);
		dup2(save_stdout, STDOUT_FILENO);
		dup2(save_stdin, STDIN_FILENO);
		char **lines = splitInput(infos, "\n");
		for (int i = 0; lines[i] != NULL; i++){
			cb_drawLine();
			char	**infos = splitInput(lines[i], ",");
			printf("Name: %s\nGrade: %s\n", infos[0], infos[1]);
			cb_free2d((void **)infos);
		}
		cb_drawLine();
		cb_free2d((void **)lines);
	}
}
