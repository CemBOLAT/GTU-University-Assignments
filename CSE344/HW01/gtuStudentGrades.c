#include "util.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


void gtuStudentGrades(char **envp){
	pid_t pid;
	pid = fork();
	if (pid < 0){
		fprintf(stderr, "Fork Failed");
		exit(1);
	}
	else if (pid == 0){
		char *args[] = {"touch", "grades.txt", NULL};
		printf("cmd: gtuStudentGrades	<file_name> should create a file.\n");
		execve("/usr/bin/touch", args, envp);
		exit(0);
	}
	else{
		wait(NULL);
	}
}
