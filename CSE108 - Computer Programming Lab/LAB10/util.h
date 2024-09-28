#ifndef UTIL_H
# define UTIL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <time.h>

# define STUDENT_NUM 10000

typedef struct s_Student
{
	int		ID;
	int		age;
	float	gpa;
} Student;

int		*init_arr(int size);
float	init_student_struct(Student *arr);
void	free_arr(int *arr);
void	print_array(int *arr, int size);
void	f_draw_line(void);

# endif
