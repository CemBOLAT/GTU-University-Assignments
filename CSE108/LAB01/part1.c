#include "util.h"

void	part1(){

	int	n;
	printf("\nTODO: Write a C program that prompts theuser to enter an integer value between 1 and 100.\nThe program prints an output bythe following operations:\n");
	printf("-->If the entered value is divisible by 3, output \"Fizz\"\n");
	printf("-->If the entered value is between 5 and 50, output \"Buzz\"\n");
	printf("-->If the entered value is divisible by 3 and between 5 and 50, output \"FizzBuzz\" \n\n");
	printf("Enter number <between 1 and 100> : ");
	scanf("%d", &n);

	while (!(n >= 1 && n <= 100)){
		printf("Invalid Input number must be <between 1 and 100> !\n");
		printf("Enter number : ");
		scanf("%d", &n);
	}
	if (n % 3 == 0){
		printf("Fizz");
	}
	if (n >= 5 && n <= 50){
		printf("Buzz");
	}
	printf("\n");
}
