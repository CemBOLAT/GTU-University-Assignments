#include <sys/types.h>
#include <sys/wait.h>
#include "util.h"
#include <stdbool.h>
#include <stdio.h>

void searchStudent() {}
void sortALL() {}
void showAll() {}
void listGrades() {}
void listSome() {}

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
				searchStudent();
				break;
			case 4:
				sortALL();
				break;
			case 5:
				showAll();
				break;
			case 6:
				listGrades();
				break;
			case 7:
				listSome();
				break;
			case 8:
				isExit = true;
				break;
		}
	}
}

