#include "util.h"

void	part2(){
	int 	x, y;
	int		max;
	float	res, float_x, float_y, float_max;
	printf("\nTODO: Write a C program that takes X and Y decimal numbers from the user and calculates the Z value by the giving formula: \n");
	printf("\nEnter first number (x) : ");
	scanf("%d", &x);
	printf("Enter second number (y) : ");
	scanf("%d", &y);
	while (y == 0 || x + y == 0){
		if (y == 0){
			printf("Invalid Input: Denominator cannot be zero ! (y)\n");
			printf("Enter second number (y) : ");
			scanf("%d", &y);
		}
		else {
			printf("Invalid Input: Denominator cannot be zero ! (x + y)\n");
			printf("Enter first number (x) : ");
			scanf("%d", &x);
			printf("Enter second number (y) : ");
			scanf("%d", &y);
		}
	}
	if (x < y){
		max = y;
	}
	else{
		max = x;
	}
	float_x = (float)x;
	float_y = (float)y;
	float_max = (float)max;
	res = (float_x / float_y) + ((float_max) / (float_x + float_y));
	printf("Z = %.3f\n", res);
}
