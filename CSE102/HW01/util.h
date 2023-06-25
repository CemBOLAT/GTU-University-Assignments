#ifndef UTIL_H
# define UTIL_H

// --> scanf and printf
#include <stdio.h>
// --> malloc and free
#include <stdlib.h>

struct part_1 {
	int nbr1;
	int nbr2;
};

struct part_2 {
	int nbr1;
	int nbr2;
};

struct part_3 {
	int nbr1;
	int nbr2;
};

struct part_4 {
	int nbr;
};

/*
	I prefer to use struct to reduces variables and use it regularly
	struct data_1 includes input numbers for task1
	struct data_2 includes input numbers for task2
	struct data_3 includes input numbers for task3
	struct data_4 includes input numbers for task4
*/
typedef struct s_main {
	struct part_1 data_1;
	struct part_2 data_2;
	struct part_3 data_3;
	struct part_4 data_4;
}t_main;

void	part1(t_main *data);
void	part2(t_main *data);
void	part3(t_main *data);
void	part4(t_main *data);

#endif
