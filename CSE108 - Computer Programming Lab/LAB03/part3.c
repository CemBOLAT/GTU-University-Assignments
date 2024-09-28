#include "util.h"

int	f_calculate_result(int *nbrs, char operation, double result);

void	part3(void)
{
	int		nbrs[2];
	char	operation;
	double	result;
	int		boolean;

	while(getchar() != '\n');
	printf("Enter an arithmetic operation (+, -, *, /) : ");
	scanf("%c", &operation);
	while (
		operation != '+' && operation != '-' \
		&& operation != '*' && operation != '/' )
	{
		printf("INVALID OPERATION !\n");
		while(getchar() != '\n');
		printf("Enter an arithmetic operation (+, -, *, /) : ");
		scanf("%c", &operation);
	}
	printf("Enter two numbers: ");
	scanf("%d %d", &nbrs[0], &nbrs[1]);
	printf("Result: ");
	scanf("%lf", &result);
	if (operation == '/' && nbrs[1] == 0)
	{
		printf("Invalid INPUT ! << denominator cannot ben zero >> \n");
		return ;
	}
	boolean = f_calculate_result(nbrs, operation, result);
	if (boolean)
		printf("Bravo, correct answer!\n");
	else
		printf("Wrong answer, try again.\n");
	draw_line();
}

int	f_calculate_result(int *nbrs, char operation, double result)
{
	int	calculated_result;

	switch (operation)
	{
		case '+' :
			calculated_result = nbrs[0] + nbrs[1];
			break;
		case '-' :
			calculated_result = nbrs[0] - nbrs[1];
			break;
		case '*' :
			calculated_result = nbrs[0] * nbrs[1];
			break;
		case '/' :
			calculated_result = nbrs[0] / nbrs[1];
			break;
	}
	if (calculated_result == result)
		return (1);
	return (0);
}
