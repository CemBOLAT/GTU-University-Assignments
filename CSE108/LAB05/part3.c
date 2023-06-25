#include "util.h"

void	f_convert(int number, int digit);
void	f_print_convert(int number, int digit, int base);
void	f_print_menu_2();

void	part3()
{
	int	option, number, digit;
	int	is_program_finished = 1;
	f_draw_line();
	printf("TODO : Write a program that calculates the base 10 equivalent of a given number and its bases 2, 8, and 16  equivalents.\n");
	while (is_program_finished == 1)
	{
		f_draw_line();
		f_print_menu_2();
		scanf("%d", &option);
		switch (option)
		{
			case 1 :
				printf("Enter a number: ");
				scanf("%d", &number);
				digit = f_digit_num(number);
				f_convert(number, digit);
				break;
			case 2 :
				is_program_finished = 0;
				f_draw_line();
				printf("\033[32mGOODBYEEE !\n\033[0m");
				break;
			default :
				f_draw_line();
				printf("INVALID INPUT !\n");
				break;
		}
	}
}

void	f_print_menu_2()
{
	printf("1. Convert a number to decimal, binary, octal, and hexadecimal\n2. Quit\nEnter your choice: ");
}

void	f_convert(int number, int digit)
{
	f_draw_line();
	printf("Decimal equivalent: ");
	f_print_convert(number, digit, 10);
	printf("Binary equivalent: ");
	f_print_convert(number, digit, 2);
	printf("Octal equivalent: ");
	f_print_convert(number, digit, 8);
	printf("Hexadecimal equivalent: ");
	f_print_convert(number, digit, 16);
}

void	f_print_convert(int number, int digit, int base)
{
	int i = 0;
	int	res = 0;
	while (i < digit)
	{
		res += (number % 10) * (pow(base, i));
		i++;
		number /= 10;
	}
	printf("%d\n", res);
}
