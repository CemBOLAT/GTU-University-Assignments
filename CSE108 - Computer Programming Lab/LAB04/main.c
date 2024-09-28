#include "util.h"

void	part1(FILE *file);
void	part2(int size);
void	part3(int size);

int main()
{
	int		is_game_finished = 1;
	int		input;
	FILE	*file;

	printf("========================================\n");
	printf("Welcome to Shape Reader! Please make your choice to continue: \n");
	printf("1-) Generate a shape file\n2-) Terminate the program\n>> ");

	scanf("%d", &input);
	while (input != 1 && input != 2)
	{
		printf("Invalid Input !\n");
		printf("1-) Read and draw a shape file\n2-) Terminate the program\n>> ");
		scanf("%d", &input);
	}
	switch (input)
	{
		case 1 :
			file = fopen(FILE_NAME, "w+");
			printf("Generated a shape file named <<< %s >>>\n", FILE_NAME);
			break;
		case 2 :
			is_game_finished = 0;
			break;
	}
	while (is_game_finished)
	{
		printf("========================================\n");
		printf("1-) Generate a shape file\n2-) Read and draw a shape file\n3-) Terminate the program\n>> ");
			scanf("%d", &input);
			while (input != 1 && input != 2 && input != 3)
			{
				printf("Invalid Input !\n");
				printf("1-) Generate a shape file\n2-) Read and draw a shape file\n3-) Terminate the program\n>> ");
				scanf("%d", &input);
			}
		switch (input)
		{
			case 1 :
				fclose(file);
				printf("Regenerated a shape file named <<< %s >>>\n", FILE_NAME);
				file = fopen(FILE_NAME, "w+");
				break;
			case 2 :
				part1(file);
				break;
			case 3 :
				is_game_finished = 0;
				fclose(file);
				break;
		}
	}
	printf("GOOODBYEEE !\n");
	return (0);
}

void	part1(FILE *file)
{
	char	shape;
	int		size;
	while (getchar() != '\n');
	printf("Enter shape properties ! (shape,size) \n>> ");
	scanf("%c,%d", &shape, &size);
	while ((size < 3 || size > 10) || !(shape == 's' || shape == 't'))
	{
		while (getchar() != '\n');
		printf("Invalid input ! << only 's' or 't' for shape and < 3-10(inclusive) for size are valid !>>\n");
		printf("Enter shape properties ! (shape,size) \n>> ");
		scanf("%c,%d", &shape, &size);
	}
	fprintf(file, "%c,%d\n", shape, size);
	printf("========================================\n");
	if (shape == 's')
		part2(size);
	else if (shape == 't')
		part3(size);
}

void	part2(int size)
{
	int	i, j;

	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size; j++)
		{
			if (i == 0 || i == size - 1)
				printf("*");
			else if (j == 0 || j == size - 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void	part3(int size)
{
	int	i = 0;
	int j, k;

	while (i < size - 1)
	{
		j = 0;
		k = 0;
		while (j < size - i - 1)
		{
			printf(" ");
			j++;
		}
		printf("*");
		while (k < (((i-1) * 2) + 1) )
		{
			printf(" ");
			k++;
		}
		if (i != 0)
			printf("*");
		printf("\n");
		i++;
	}
	for (int i = 0; i < (size * 2) - 1; i++)
		printf("*");
	printf("\n");
}

