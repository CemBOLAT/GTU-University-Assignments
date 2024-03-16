#pragma once

#ifndef FILENAME
# define FILENAME "gradest.txt"
#endif

typedef struct s_Student {
	char name[50];
	char grade[10];
} Student;

int		printMenu();
void	printInformation();
void	printUsage();
void	gtuStudentGrades(char **envp);
void	addStudentGrade();
void	searchStudent();
void	sortALL();
void	showAll();
void	listGrades();
void	listSome();
void	pathFinder(char **env, char *command);

