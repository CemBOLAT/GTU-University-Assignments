#include "util.h"

void	f_draw_line()
{
	printf("\033[36m========================================\n\033[0m");
}

int	f_digit_num(int number)
{
	int i = 0;
	while (number != 0)
	{
		number /= 10;
		i++;
	}
	return (i);
}
