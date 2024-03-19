#pragma once

#ifndef FILENAME
# define FILENAME "grades.txt"
#endif

#include <stdbool.h>

typedef struct s_Student {
	char name[50];
	char grade[10];
} Student;

int		printMenu();
void	printInformation();
void	printUsage();
void	gtuStudentGrades(char **envp);
void	addStudentGrade(char **envp);
void	addStudentGrade();
void	searchStudent();
void	sortALL(char **envp);
void listSome(char **envp);
void	showAll();
void	listGrades(char **envp);
void	listSome();
char	*pathFinder(char **env, char *command);
void	cb_free(void *data);
void	cb_free2d(void **data);
int		cb_len2d(void **data);
int		cb_nbrOfWords(char *input, char *delim);
char	*takeInput(char *message);
char	**splitInput(char *input, char *delim);
void	searchStudent(char **env);
void	showAll(char **env);
void	cb_drawLine();
void	cb_toUpper(char *str);
char	*cb_trim(char *str);
char	*cb_capitalize(char *str);
bool	isValidGrade(char *grade);
char	*cb_itoa(int num);
