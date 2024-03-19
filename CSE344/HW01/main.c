#include <sys/types.h>
#include <sys/wait.h>
#include "util.h"
#include <stdbool.h>
#include <stdio.h>

int main(int argc, char *argv[], char *envp[]) {
	bool isExit = false;
	int	input;
	// char	*path = pathFinder(envp, "ls");
	// printf("%s\n", path);
	// cb_free((void *)path);
	printInformation();
	while (!isExit){
		input = printMenu();
		switch (input){
			case 0:
				printUsage();
				break;
			case 1:
				gtuStudentGrades(envp);
				break;
			case 2:
				addStudentGrade(envp);
				break;
			case 3:
				searchStudent(envp);
				break;
			case 4:
				sortALL(envp);
				break;
			case 5:
				showAll(envp);
				break;
			case 6:
				listGrades(envp);
				break;
			case 7:
				listSome(envp);
				break;
			case 8:
				isExit = true;
				break;
		}
	}
}

