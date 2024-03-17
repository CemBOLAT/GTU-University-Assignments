#include "util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

static bool isInputValid(char **spInput)
{
	if (spInput[0] == NULL || spInput[0][0] == '\0' || spInput[1] != NULL)
	{
		if (spInput[0] == NULL || spInput[0][0] == '\0')
		{
			fprintf(stderr, "No file name is given\n");
		}
		else
			fprintf(stderr, "Too many arguments are given\n");
		cb_free2d((void **)spInput);
		return false;
	}
	return true;
}

static void cb_cleanUp(char *input, char **spInput)
{
	cb_free((void *)input);
	cb_free2d((void **)spInput);
}

void gtuStudentGrades(char **envp){
	pid_t	pid;
	char 	*input = takeInput("Enter the file name: ");
	char	**spInput = splitInput(input, " ");
	if (!isInputValid(spInput)) {
		cb_cleanUp(input, spInput);
		return;
	}
	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Fork Failed");
		cb_cleanUp(input, spInput);
		exit(1);
	}
	else if (pid == 0){
		//char *args[] = {"touch", "grades.txt", NULL};
		char	*cmdPath = pathFinder(envp, "touch");
		char	*args[] = {cmdPath, spInput[0], NULL};
		execve(cmdPath, args, envp);
	}
	else{
		waitpid(pid, NULL, 0);
		cb_cleanUp(input, spInput);
	}
}
