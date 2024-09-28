# include <stdio.h>

# define	ARRAY_SIZE 20
# define	SENTINEL -100
# define	FILE_NAME "./text.txt"

void	f_draw_line(void);
void	part1(void);
void	part2(void);

int main(void)
{
	f_draw_line();
	part1();
	f_draw_line();
	part2();
}

//==========================================part1======================================

void	f_print_menu_1(void);
void	f_fill_array(int arr[ARRAY_SIZE]);
void	f_fill_array2(char arr[ARRAY_SIZE]);
void	f_fill_array3(float arr[20]);
void	f_fill_letter(char letter[ARRAY_SIZE], int arr[ARRAY_SIZE], int i);

void	part1()
{
	int		arr[ARRAY_SIZE];
	char	letter_arr[ARRAY_SIZE];
	int		i = 0;
	f_fill_array(arr);
	f_fill_array2(letter_arr);

	while (1)
	{
		f_print_menu_1();
		scanf("%d", &arr[i]);
		if (arr[i] == SENTINEL)
			break ;
		i++;
	}
	f_fill_letter(letter_arr, arr, i);
	f_draw_line();
	for (int j = 0; j < i; j++)
		printf("%d %c\n",arr[j], letter_arr[j]);
	return ;
}

void	f_print_menu_1(void)
{
	printf("Enter a integer number ! \n >> ");
}

void	f_fill_array(int arr[20])
{
	for (int i = 0; i < ARRAY_SIZE; i++)
		arr[i] = 0;
}

void	f_fill_array2(char arr[20])
{
	for (int i = 0; i < ARRAY_SIZE; i++)
		arr[i] = '\0';
}

void	f_fill_array3(float arr[20])
{
	for (int i = 0; i < ARRAY_SIZE; i++)
		arr[i] = 0;
}

void	f_fill_letter(char letter[ARRAY_SIZE], int arr[ARRAY_SIZE], int i)
{
	int	j = 0;
	while (j < i)
	{
		if (arr[j] % 2 == 1 || arr[j] % 2 == -1)
			letter[j] = 'o';
		else
			letter[j] = 'e';
		j++;
	}
}
//===========================================part 2=======================================

int		f_team(char team[ARRAY_SIZE], char input, int row);
float	f_get_total_salary(char team[ARRAY_SIZE], float salary[ARRAY_SIZE], char input, int row);

void	part2()
{
	FILE	*file;
	int		row, number_of_fans;
	char	occupation[ARRAY_SIZE], team[ARRAY_SIZE], input;
	int		age[ARRAY_SIZE];
	float	salary[ARRAY_SIZE], total_salary = 0;

	f_fill_array(age);
	f_fill_array2(occupation);
	f_fill_array2(team);
	f_fill_array3(salary);

	file = fopen(FILE_NAME, "r");
	fscanf(file, "%d\n", &row);

	for (int i = 0; i < row; i++)
		fscanf(file, "%d %c %f %c\n", &age[i], &occupation[i], &salary[i], &team[i]);

	while (getchar() != '\n');
	printf("Please select a team: ");
	scanf("%c", &input);
	number_of_fans = f_team(team, input, row);
	if (number_of_fans == 0)
		printf("There are no fans of %c in the database!\n", input);
	else
	{
		total_salary = f_get_total_salary(team, salary, input, row);
		printf("Average salaries of fans of %c: %.1lf\n", input, total_salary / number_of_fans);
	}
	fclose(file);
	return ;
}

int	f_team(char team[ARRAY_SIZE], char input, int row)
{
	int	res = 0;

	for(int i = 0; i < row; i++)
	{
		if (team[i] == input)
			res++;
	}
	return (res);
}

float	f_get_total_salary(char team[ARRAY_SIZE], float salary[ARRAY_SIZE], char input, int row)
{
	float	res = 0;

	for(int i = 0; i < row; i++)
	{
		if (team[i] == input)
			res += salary[i];
	}
	return (res);
}

//==================================PART2==================================

void	f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}
