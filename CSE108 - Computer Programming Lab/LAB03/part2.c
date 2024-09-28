#include "util.h"

void	f_get_grades(int score);

void	part2(void)
{
	int		scores[3];
	double	total;
	printf("Enter 3 scores: ");
	scanf("%d %d %d", &scores[0], &scores[1], &scores[2]);

	while (	scores[0] > 100 || scores[0] < 0 ||
			scores[1] > 100 || scores[1] < 0 ||
			scores[2] > 100 || scores[2] < 0)
	{
		printf("Invalid Input: Your scores must be between 0-100\n");
		printf("Enter 3 scores: ");
		scanf("%d %d %d", &scores[0], &scores[1], &scores[2]);
	}
	total = (scores[0] + scores[1] + scores[2]);
	printf("Your letter grades are ");
	f_get_grades((int)(scores[0] / 10));
	printf(", ");
	f_get_grades((int)(scores[1] / 10));
	printf(" and ");
	f_get_grades((int)(scores[2] / 10));
	printf(" with an %.1lf average", total / 3);
	printf("\n");
	draw_line();
}

void	f_get_grades(int score)
{
	switch(score)
	{
		case 10 :
			printf("A+");
			break;
		case 9 :
			printf("A+");
			break;
		case 8 :
			printf("A");
			break;
		case 7 :
			printf("B+");
			break;
		case 6 :
			printf("B");
			break;
		case 5 :
			printf("C");
			break;
		case 4 :
			printf("D");
			break;
		default :
			printf("F");
	}
}
