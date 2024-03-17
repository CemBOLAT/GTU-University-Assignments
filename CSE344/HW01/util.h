#pragma once

#ifndef FILENAME
# define FILENAME "grades.txt"
#endif

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
void	sortALL();
void	showAll();
void	listGrades();
void	listSome();
char	*pathFinder(char **env, char *command);
void	cb_free(void *data);
void	cb_free2d(void **data);
int		cb_len2d(void **data);
int		cb_nbrOfWords(char *input, char *delim);
char	*takeInput(char *message);
char	**splitInput(char *input, char *delim);
void	searchStudent(char **env);
