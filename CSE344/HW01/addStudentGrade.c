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

static bool isInputValid(char **spInput)
{
	if (spInput[0] == NULL || spInput[0][0] == '\0' || spInput[1] == NULL || spInput[1][0] == '\0')
	{
		if (spInput[0] == NULL || spInput[0][0] == '\0')
		{
			fprintf(stderr, "No student name is given\n");
		}
		else if (spInput[1] == NULL || spInput[1][0] == '\0')
		{
			fprintf(stderr, "No grade is given\n");
		}
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

static char	*cb_concat(char **spInput)
{
	int 	i = 0;
	char	*result = (char *)malloc(1);
	while (spInput[i + 1] != NULL)
	{
		result = (char *)realloc(result, strlen(result) + strlen(spInput[i]) + 1);
		strcat(result, spInput[i]);
		i++;
		if (spInput[i + 1] != NULL)
			strcat(result, " ");
	}
	result = (char *)realloc(result, strlen(result) + strlen(spInput[i]) + 1);
	strcat(result, ",");
	strcat(result, spInput[i]);
	result[strlen(result)] = '\0';
	return result;
}

void addStudentGrade(char **envp)
{
	pid_t	pid;
	char 	*input = takeInput("Enter the student name and grade: ");
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
		char	*cmdPath = pathFinder(envp, "echo");
		printf("%s\n", cmdPath);
		char	*convertToADD = cb_concat(spInput);
		FILE	*file = fopen("grades.txt", "a");
		if (file == NULL){
			fprintf(stderr, "File could not be opened\n");
			cb_cleanUp(input, spInput);
			exit(1);
		}
		fprintf(file, "%s\n", convertToADD);
		exit(0);
	}
	else{
		waitpid(pid, NULL, 0);
		cb_cleanUp(input, spInput);
	}
}
