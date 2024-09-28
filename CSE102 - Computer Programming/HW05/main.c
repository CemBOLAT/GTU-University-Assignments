# include <stdio.h>
// sqrt()
# include <math.h>

typedef enum {
	RED,
	GREEN,
	BLUE,
	YELLOW,
	ORANGE,
} Color;

/* printing blue lines to increase visibility */
void	f_draw_line(void);
/* printing homework banner to increase visibility */
void	print_banner(void);
void	part1(void);
void	part2(void);
void	part3(void);

int main(void)
{
	print_banner();
	part1();
	part2();
	part3();
}

//==========================================part1======================================

// printing output for part1
void	print_output_1(int occurence[]);
// filling array with zeros to count occurence of each letter properly
void	fill_array_zero(int occurence[]);
// making program case-insensitive
void	handle_case_conversation(int occurence[], char letter);

void	part1()
{
	int		occurence[26];
	char	file_name[20];
	FILE	*file;
	char	letter;
	printf("TODO: Develop a program that reads a text file and counts the occurrences of each letter in the English alphabet (case-insensitive).\n");
	f_draw_line();
	printf("Enter the file name: ");
	scanf("%s", file_name); // takinig input
	file = fopen(file_name, "r");
	while (file == NULL) // file control
	{
		printf("Invalid file name !\n");
		f_draw_line();
		while(getchar() != '\n');
		printf("Enter the file name: ");
		scanf("%s", file_name);
		file = fopen(file_name, "r");
	}
	fill_array_zero(occurence); // fill with 0
	while (fscanf(file, "%c", &letter) != -1)
	{
		if (letter > 0) // ascii control
			handle_case_conversation(occurence, letter);
		else // if the letter is not in english 'ü' 'ı' etc. program prints error!
		{
			printf("Your file has some letter(s) that is not in english alphabet ! \n");
			f_draw_line();
			fclose(file);
			return ;
		}
	}
	// printing output
	print_output_1(occurence);
	// closing file stream
	fclose(file);
	return ;
}

void	handle_case_conversation(int occurence[], char letter)
{
	// filling occurence of letter respect to their position in alphabet
	if (letter - 'a' <= 'z' - 'a' && letter - 'a' >= 0)
		occurence[letter - 'a'] += 1;
	else if (letter - 'A' <= 'Z' - 'A' && letter - 'A' >= 0)
		occurence[letter - 'A'] += 1;
}

void	fill_array_zero(int occurence[])
{
	for(int i = 0; i < 26; i++)
		occurence[i] = 0;
}

void	print_output_1(int occurence[])
{
	char	letter = 'A';

	f_draw_line();
	printf("Letter Frequency: \n");
	while (letter <= 'Z')
	{
		printf("%c: %d\n", letter, occurence[letter - 'A']);
		letter++;
	}
	f_draw_line();
}

//===========================================part 2=======================================

// assinging colors to Color enum respect to input
Color	assign_color(char letter);
// color mixer function as pdf's need
Color	colorMixer(Color color1, Color color2, Color (*mix_color)(Color, Color));
// mixing_colors and printing output
Color	mix_color(Color color1, Color color2);
// calculating the distance between color vectors
double	euclidean_al(double p1[3], double p2[3]);
// printing mixed color name
void	print_color(int index);
// printing output as pdf's way for ex: [0,0, 0,5, 0,20]
void	print_color_percentage(double color[3], void (*print_each_part)(double));
// printing each part of vector to make output exactly the same as pdf's way
void	print_each_part(double nbr);

void	part2()
{
	Color	color1;
	Color	color2;
	Color	mixed_color;
	char	letter, letter2;

	printf("TODO: MIXING COLORS!\n");
	f_draw_line();
	while (getchar() != '\n');
	printf("Enter Color 1 (r,g,b,y,o): ");
	scanf("%c", &letter); //taking input
	while (!(letter == 'r' || letter == 'g' || letter == 'b' || letter == 'y' || letter == 'o')) //input check
	{
		printf("INVALID INPUT !\n");
		while (getchar() != '\n');
		printf("Enter Color 1 (r,g,b,y,o): ");
		scanf("%c", &letter);
	}
	color1 = assign_color(letter); // assinging color to enum respect to letter
	while (getchar() != '\n');
	printf("Enter Color 2 (r,g,b,y,o): ");
	scanf("%c", &letter2); //taking input
	while (!(letter2 == 'r' || letter2 == 'g' || letter2 == 'b' || letter2 == 'y' || letter2 == 'o')) //input check
	{
		printf("INVALID INPUT !\n");
		while (getchar() != '\n');
		printf("Enter Color 2 (r,g,b,y,o): ");
		scanf("%c", &letter2);
	}
	color2 = assign_color(letter2); // assinging color to enum respect to letter
	mixed_color = colorMixer(color1, color2, mix_color); // mix the color
	return ;
}

Color	mix_color(Color color1, Color color2)
{
	double arr[5][3] = {{1,0,0},
						{0,1,0},
						{0,0,1},
						{0.5,0.5,0},
						{0.5,0.4,0.2}};
	double	m_color[3] = {0,0,0};
	double	closest = 0;
	double	temp = 0;
	int		index = 0;
	Color	res;

	// color mixed vector
	for (int i = 0; i < 3; i++)
		m_color[i] = (arr[color1][i] + arr[color2][i]) / 2;

	// finding closest color with selection algoritm
	closest = euclidean_al(m_color, arr[0]);
	for (int i = 0; i < 5; i++)
	{
		temp = euclidean_al(m_color, arr[i]);
		if (temp <= closest)
		{
			closest = temp;
			index = i;
		}
	}
	// printing color name respect to input
	print_color(index);
	// printing mixed colors vectors respect to output
	print_color_percentage(arr[index], print_each_part);
	res = index;
	return (res);
}

void	print_color_percentage(double color[3], void (*print_each_part)(double))
{
	printf("[");
	print_each_part(color[0]);
	printf(", ");
	print_each_part(color[1]);
	printf(", ");
	print_each_part(color[2]);
	printf("]\n");
}

void	print_each_part(double nbr)
{
	if (nbr == (int)nbr)
		printf("%d.0",(int)nbr);
	else
		printf("%g", nbr);
}

void	print_color(int index)
{
	switch(index)
	{
		case 0 :
			printf("RED ");
			break;
		case 1 :
			printf("GREEN ");
			break;
		case 2 :
			printf("BLUE ");
			break;
		case 3 :
			printf("YELLOW ");
			break;
		case 4 :
			printf("ORANGE ");
			break;
	}
}

Color	colorMixer(Color color1, Color color2, Color (*mix_color)(Color, Color))
{
	Color	mixed_color;
	printf("Mixed Color: ");
	mixed_color = mix_color(color1, color2);
	return (mixed_color);
}

double	euclidean_al(double p1[3], double p2[3])
{
	double	r[3] = {0,0,0};
	double	total;
	for(int i = 0; i < 3 ; i++)
		r[i] = (p1[i] - p2[i]) * (p1[i] - p2[i]);
	total = r[0] + r[1] + r[2];

	return (sqrt(total));
}

Color	assign_color(char letter)
{
	switch (letter)
	{
	case 'r':
		return (0);
	case 'g':
		return (1);
	case 'b':
		return (2);
	case 'y':
		return (3);
	case 'o':
		return (4);
	default:
		return (-1); // error flag
	}
}

//==================================PART2==================================
//==================================PART3==================================


// printing user the message who's turn is
void	print_user_message(int moves);
// putting X or O to board respect to who's turn is
void	make_move(char board[3][3], int row, int col, int move);
// printing board after each move
void	print_board(char board[3][3]);
// winners control
int		is_someone_win(char board[3][3]);
// cleaning board after each game
void	f_clean_board(char board[3][3]);
// printing menu
void	f_print_menu();

void	part3()
{
	char	board[3][3];
	int		is_game_finished = 1;
	int		moves = 0;
	int		row,col;
	int		choose;

	f_draw_line();
	printf("TODO: Tic-Tac-Toe\n");
	f_draw_line();
	while (is_game_finished == 1) // flag
	{
		f_print_menu();
		scanf("%d", &choose);
		while (choose < 0 || choose > 2)
		{
			printf("INVALID INPUT ! \n");
			f_print_menu();
			scanf("%d", &choose);
		}
		if (choose == 1)
		{
			moves = 0;
			f_clean_board(board);
			while (moves < 9 && is_someone_win(board) == 0)
			{
				print_user_message(moves);
				scanf("%d %d", &row, &col);
				while ((row < 0 || row > 2 || col < 0 || col > 2) || board[row][col] == 'X' || board[row][col] == 'O') // input check
				{
					printf("INVALID MOVE !\n");
					print_user_message(moves);
					scanf("%d %d", &row, &col);
				}
				make_move(board, row, col, moves); //updating board array
				print_board(board); // prints updated board
				moves++;
			}
			f_draw_line();
			if (is_someone_win(board) == 1)
			{
				if (moves % 2 == 1)
					printf("Player 1 (X) wins!\n");
				else
					printf("Player 2 (O) wins!\n");
			}
			else
				printf("GAME TIED !\n");
			f_draw_line();
		}
		else if (choose == 2)
		{
			printf("GOODBYE \n");
			is_game_finished = 0;
		}
	}
}

void	print_user_message(int moves)
{
	if (moves % 2 == 0)
		printf("Player 1 (X), enter your move (row, col): ");
	else
		printf("Player 2 (O), enter your move (row, col): ");
}

void	make_move(char board[3][3], int row, int col, int move)
{
	if (move % 2 == 0)
		board[row][col] = 'X';
	else
		board[row][col] = 'O';
}

void	print_board(char	board[3][3])
{
	for(int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (board[i][j] == 'X')
				printf("X ");
			else if (board[i][j] == 'O')
				printf("O ");
			else
				printf("_ ");
		}
		printf("\n");
	}
}

int		is_someone_win(char	board[3][3])
{
	for (int i = 0; i < 3; i++) {
		if (board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X')
			return 1;
		else if (board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O')
			return 1;
	}
	for (int i = 0; i < 3; i++) {
		if (board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X')
			return 1;
		else if (board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O')
			return 1;
	}
	if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
			return 1;
	else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O')
			return 1;
	else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X')
			return 1;
	else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O')
			return 1;
	return (0);
}

void	f_print_menu()
{
	printf("Make a choice ! \n1.Start New Game !\n2.Exit\n >> ");
}

void	f_clean_board(char board[3][3])
{
	int i = 0, j = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			board[i][j] = ' ';
			j++;
		}
		i++;
	}
}

//==================================PART3==================================

/* printing homework banner to increase visibility */
void print_banner(void)
{
	f_draw_line();
	printf("\n\033[32m \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >======>     >=>   >=>\n \
	>=>    >=>   >=>    >=>   >> >=>   >>=> >=>       >=>        >=>   >=>    >=>   >=>    >=>   >=>  >=>                 >=>          >=>>==>  \n \
	>=>    >=> >=>        >=> >=> >=> > >=> >=>       >=>   >>   >=> >=>        >=> >=>    >=>   >=> >=>                >=>  >=>      >=>\n \
	>=====>>=> >=>        >=> >=>  >=>  >=> >=====>   >=>  >=>   >=> >=>        >=> >> >==>      >>=>>       >====>   >=>     >=>    >==>     \n \
	>=>    >=> >=>        >=> >=>   >>  >=> >=>       >=> >> >=> >=> >=>        >=> >=>  >=>     >=>  >=>    >====>   >=>      >=>      >=>\n \
	>=>    >=>   >=>     >=>  >=>       >=> >=>       >> >>    >===>   >=>     >=>  >=>    >=>   >=>   >=>             >=>    >=>         >=> \n \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >=>      >=> >=>     >=>             >==>        >==>>=> \n \
	\t\t\t\t\t CEMAL BOLAT 210104004010 \033[0m\n\n");
	f_draw_line();
}

/* printing blue lines to increase visibility */
void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}
