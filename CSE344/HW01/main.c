#include <sys/types.h>
#include <sys/wait.h>
#include "util.h"
#include <stdbool.h>

void addStudentGrade() {}
void searchStudent() {}
void sortALL() {}
void showAll() {}
void listGrades() {}
void listSome() {}

int main(int argc, char *argv[], char *envp[]) {
	bool isExit = false;
	int	input;
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
				addStudentGrade();
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

