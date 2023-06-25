#include "util.h"

int		is_valid_input(int number);
void	f_print_reverse(int number, int digit);

void	part2()
{
	int	digit;
	int	number;
	printf("TODO : Write a  C  program  that  reverses  an  integer  entered  by  the  user.\n");
	f_draw_line();
	printf("Enter a number (3,4, or 5): ");
	scanf("%d", &number);
	while (is_valid_input(number) == 0)
	{
		printf("Invalid Input! \n");
		printf("Enter a number (3,4, or 5): ");
		scanf("%d", &number);
	}
	digit = f_digit_num(number);
	f_print_reverse(number, digit);
}

int	is_valid_input(int number)
{
	if (number > 99 && number <= 99999)
		return (1);
	return (0);
}

void	f_print_reverse(int number, int digit)
{
	int	i = 0;
	printf("Reversed number: ");
	while (i < digit)
	{
		printf("%d", number % 10);
		number /= 10;
		i++;
	}
	printf("\n");
}
