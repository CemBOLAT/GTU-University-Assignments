#include <stdio.h>
#include <stdbool.h>

void printMenu();
void diamondScape();
void pascalTriangle();
bool takeContinueOption();
int	factorial(int n);
int	combination(int u, int d);

int main()
{
	bool isExit = false;

	while (!isExit)
	{
		printMenu();
		int choice;
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			diamondScape();
			break;
		case 2:
			pascalTriangle();
			break;
		case 3:
			printf("Program is terminating...\n");
			isExit = true;
			break;
		default:
			printf("Invalid choice\n");
		}
		if (choice != 3)
			isExit = takeContinueOption();
	}
}

void pascalTriangle(){
	int n, i, j;

	do {
		printf("Enter the number of rows: ");
		scanf("%d", &n);
		if (n < 0)
		{
			printf("Invalid number of rows\n");
		}
	} while (n < 0);

	for (i = 0; i < n; i++){
		for (j = 0; j <= n - i; j++){
			printf(" ");
		}
		for (j = 0; j <= i; j++){
			//printf("%d", factorial(i) / (factorial(j) * factorial(i - j)));
			int nbr = combination(i, j);
			if (nbr % 2 == 0){
				printf("  ");
			}
			else{
				printf("* ");
			}
		}
		printf("\n");
	}
}

void diamondScape()
{
	int n;

	do {
		printf("Enter the number of rows: ");
		scanf("%d", &n);
		if (n < 0)
		{
			printf("Invalid number of rows\n");
		}
	} while (n < 0);

	if (n % 2 == 0)
	{
		n += 1;
	}
	for (int i = 0; i < (n / 2); i++)
	{
		for (int j = 0; j < (n / 2) - i; j++)
		{
			printf(" ");
		}
		for (int j = 0; j < (2 * i) + 1; j++)
		{
			printf("*");
		}
		printf("\n");
	}
	for (int i = 0; i < n; i++)
	{
		printf("*");
	}
	printf("\n");
	for (int i = 0; i < (n / 2); i++)
	{
		for (int j = 0; j <= i; j++)
		{
			printf(" ");
		}
		for (int j = 0; j < n - (2 * (i + 1)); j++)
		{
			printf("*");
		}
		printf("\n");
	}
}

bool takeContinueOption()
{
	int choice;
	do {
		printf("Do you want to continue? (1/0): 1 for yes, 0 for no: ");
		scanf("%d", &choice);
		if (choice != 1 && choice != 0)
		{
			printf("Invalid choice\n");
		}
	} while (choice != 1 && choice != 0);
	return choice == 0;
}

void printMenu()
{
	printf("1. Diamond Scape\n");
	printf("2. Pascal Triangle\n");
	printf("3. Exit\n");
}

int	factorial(int i){
	if (i == 0){
		return 1;
	}
	return (i * factorial(i - 1));
}

int	combination(int u, int d){
	return factorial(u) / (factorial(d) * factorial(u - d));
}
