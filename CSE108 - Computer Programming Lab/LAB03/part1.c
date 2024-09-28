#include "util.h"

void	part1(void)
{
	int	nbrs[3];

	printf("Enter 3 integers: ");
	scanf("%d %d %d", &nbrs[0], &nbrs[1], &nbrs[2]);

	if (nbrs[0] >= nbrs[1])
	{
		if (nbrs[1] >= nbrs[2])
			printf("Median number is %d", nbrs[1]);
		else if (nbrs[2] >= nbrs[0])
			printf("Median number is %d", nbrs[0]);
		else
			printf("Median number is %d", nbrs[2]);
	}
	else if (nbrs[1] >= nbrs[2])
	{
		if (nbrs[2] >= nbrs[0])
			printf("Median number is %d", nbrs[2]);
		else if (nbrs[0] >= nbrs[1])
			printf("Median number is %d", nbrs[1]);
		else
			printf("Median number is %d", nbrs[0]);
	}
	printf("\n");
	draw_line();
}
