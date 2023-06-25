#include "util.h"

void	age_point(int *point, int age){
	if (age >= 20 && age <= 50){
		*point += 2;
	}
	else if (age > 50){
		*point += 3;
	}
}

void	exp_point(int *point, int exp){
	if (exp > 10){
		*point += 1;
	}
}

void	part3(){
	int exps[2] = {0, 10};
	int salaries[5] = {10000, 0, 15000, 20000, 25000};
	int ages[3] = {0, 20, 50};

	int age, exp;
	int point = 0;
	printf("\nTODO: Write a C  program that prompts the user to enter age and years of experience of an employer to calculate and print her/his salary by the table :\n");
	printf("Enter your age : ");
	scanf("%d", &age);
	printf("Enter your year of experience : ");
	scanf("%d", &exp);
	while (age <= 0 || exp <= 0 || exp >= age){
		if (age <= 0){
			printf("Invalid Age: You cannot be negative or zero aged\n");
			printf("Enter your age : ");
			scanf("%d", &age);
		}
		else if (exp <= 0){
			printf("Invalid Year: You cannot be negative or zero experienced\n");
			printf("Enter your year of experience : ");
			scanf("%d", &exp);
		}
		else if (exp >= age){
			printf("Invalid Input: You cannot experienced at that age\n");
			printf("Enter your year of experience : ");
			scanf("%d", &exp);
		}
	}
	age_point(&point, age);
	exp_point(&point, exp);
	if (point == 1){
		printf("Error !\n");
	}
	else {
		printf("Salary: %d\n", salaries[point]);
	}
}
