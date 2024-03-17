#include "util.h"
#include <stdio.h>
#include <stdlib.h>

int printMenu()
{
	int input;
	do
	{
		printf("Please enter a command: \n");
		printf("0. usage\n");
		printf("1. gtuStudentGrades\n");
		printf("2. addStudentGrade\n");
		printf("3. searchStudent\n");
		printf("4. sortALL\n");
		printf("5. showAll\n");
		printf("6. listGrades\n");
		printf("7. listSome\n");
		printf("8. exit\n");
		printf(">> ");
		scanf("%d", &input);
		if (input < 0 || input > 8)
		{
			printf("Invalid input. Please enter a number between 0 and 8\n");
		}
	} while (input < 0 || input > 8);
	return input;

	/*
	5. Logging: Create a log file that records the completion of each task as desired.
	6. Usage: The user should be able to display all of the available commands by calling
	gtuStudentGrades without an argument.
	gtuStudentGrades
	command without arguments should list all of the instructions or information provided
	about how commands in your program

	*/
}

void	printUsage(){
	printf("cmd: gtuStudentGrades	<file_name> should create a file.\n");
	printf("cmd: addStudentGrade	<name surname><grade> command should append student and grade to the end of the file.\n");
	printf("cmd: searchStudent	<name surname> command should return student name surname and grade.\n");
	printf("cmd: sortALL		<file_name> command should print all of the entries sorted by their names\n");
	printf("cmd: showAll		<file_name> command should print all of the entries\n");
	printf("cmd: listGrades		<file_name> command should print all of the grades\n");
	printf("cmd: listSome		<numberOfEntries> <PageNumber> <file_name> command should print the entries in the given page number.\n");
	// e.g. listSome 5 2 grades.txt command will list entries between 5th and 10th.
	printf("cmd: exit\n");
}

void printInformation()
{
	printf("This program is written by Cemal BOLAT\n");
	printf("Student ID: 210104004010\n");
}

char	*takeInput(char *message){
	char *input = (char *)malloc(100); // also take spaces
	printf("%s", message);
	// scan end of line
	scanf(" %[^\n]", input);
	return input;
}
