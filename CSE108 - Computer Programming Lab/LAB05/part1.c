#include "util.h"

void	f_print_menu();
void	convert_c_to_f();
void	convert_f_to_c();

void	part1()
{
	int	option;
	int	is_program_finished = 1;
	f_draw_line();
	printf("TODO: Temperature conversion  program that can convert temperatures between Celsius and Fahrenheit scales\n");
	while (is_program_finished == 1)
	{
		f_print_menu();
		scanf("%d", &option);
		f_draw_line();
		switch (option)
		{
			case 1 :
				convert_c_to_f();
				break;
			case 2 :
				convert_f_to_c();
				break;
			case 3 :
				is_program_finished = 0;
				printf("\033[32mGOODBYEEE !\n\033[0m");
				f_draw_line();
				break;
			default :
				printf("\033[31mINVALID INPUT !\n\033[0m");
				break;
		}
	}
}

void	f_print_menu()
{
	f_draw_line();
	printf("1. Convert Celsius to Fahrenheit\n2. Convert Fahrenheit to Celsius\n3. Quit\nEnter your choice (1-3): ");
}

void	convert_c_to_f()
{
	double	temp;
	printf("Enter the temperature value to convert: ");
	scanf("%lf", &temp);
	printf("%.2lf Celsius = %.2lf Fahrenheit\n", temp, ((temp * 9) / 5) + 32);
}

void	convert_f_to_c()
{
	double	temp;
	printf("Enter the temperature value to convert: ");
	scanf("%lf", &temp);
	printf("%.2lf Fahrenheit = %.2lf Celcius\n", temp, ((temp - 32) * 5) / 9);
}
