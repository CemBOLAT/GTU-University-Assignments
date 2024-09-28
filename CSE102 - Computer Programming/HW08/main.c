#include "util.h"

int main()
{
	m_data	data;	// struct
	int		input = -1; // menu input

	while (input != 4) {
		print_menu(); // print menu
		scanf("%d", &input);
		switch (input){
			case 1: play_game(&data); break; // play game
			case 2: play_game_pc(&data); break; // play game with computer
			case 3: show_best_score(); break; // show best score
			case 4: printf("\nProgram terminated...\n"); break; // exit
			default: printf("\nInvalid input!\n\n"); break; // error message to user
		}
	}
}

void play_game(m_data *data)
{
	int		score = MAX_SCORE, moves = 0; // to store score and moves
	int		input = -1;		// to store input
	char	letter[20];		// to store direction

	init_board(data);
	clear_file(USER);
	while (isSolvable(data->board) == 0) init_board(data);

	while (score > 0)
	{	// game is continue when score is more than 0
		print_board(data, USER); // print board
		printf("\nEnter your move (number-direction, e.g., 2-R): ");
		scanf("%d-%s", &input, letter);
		while (strlen(letter) != 1 || move(data, input, letter, &moves) == 0)
		{ // while input is not valid
			printf("%d-%s is an illegal move !!! Make a legal move!!!\n", input, letter);
			print_board_1(data);
			printf("\nEnter your move (number-direction, e.g., 2-R): ");
			scanf("%d-%s", &input, letter);
		}
		score -= DECREASE; // decrease score
		if (check_board(data) == 1)
		{ // if board is solved
			print_board(data, USER);
			print_finish(moves, score, 1);
			best_score_check(score);
			break;
		}
		if (score == 0)
		{ // if score is 0
			print_finish(moves, score, 0);
		}
	}
}

void show_best_score(void)
{
	FILE *file;
	char letter;
	file = fopen(BEST, "r");
	printf("\n");
	if (fscanf(file, "%c", &letter) == -1)
	{
		printf("No best score yet!\n\n");
		fclose(file);
		return;
	}
	printf("%c", letter);
	while (fscanf(file, "%c", &letter) != -1) printf("%c", letter);
	printf("\n\n");
	fclose(file);
}

int move(m_data *data, int input, char *letter, int *moves)
{ // to move (if not valid return 0)
	if (input < 1 || input > 8)
		return (0);
	if (strcmp(letter, "U") != 0 && strcmp(letter, "D") != 0 && strcmp(letter, "L") != 0 && strcmp(letter, "R") != 0)
		return (0);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (data->board[i][j] == input + '0') // if input is found
			{
				if (*letter == 'U')
				{
					if (*letter == 'U' && i == 0) return 0; // if input is in first row is not valid
					if (data->board[i - 1][j] == '_')
					{
						data->board[i - 1][j] = data->board[i][j];
						data->board[i][j] = '_';
						(*moves) += 1;
						return (1);
					}
					return (0);
				}
				if (*letter == 'D')
				{
					if (*letter == 'D' && i == 2) return 0; // if input is in last row is not valid
					if (data->board[i + 1][j] == '_')
					{
						data->board[i + 1][j] = data->board[i][j];
						data->board[i][j] = '_';
						(*moves) += 1;
						return (1);
					}
					return (0);
				}
				if (*letter == 'L')
				{
					if (*letter == 'L' && j == 0) return 0; // if input is in first column is not valid
					if (data->board[i][j - 1] == '_')
					{
						data->board[i][j - 1] = data->board[i][j];
						data->board[i][j] = '_';
						(*moves) += 1;
						return (1);
					}
					return (0);
				}
				if (*letter == 'R')
				{
					if (*letter == 'R' && j == 2) return 0; // if input is in last column is not valid
					if (data->board[i][j + 1] == '_')
					{
						data->board[i][j + 1] = data->board[i][j];
						data->board[i][j] = '_';
						(*moves) += 1;
						return (1);
					}
					return (0);
				}
			}
		}
	}
	return (0);
}

void print_board(m_data *data, char *file_name)
{	// to print board
	FILE *file = fopen(file_name, "a");
	printf("\n");
	fprintf(file, "\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (data->board[i][j] == '_' || data->board[i][j] == '\0')
			{
				printf("_ ");
				fprintf(file, "_ ");
			}
			else
			{
				printf("%c ", data->board[i][j]);
				fprintf(file, "%c ", data->board[i][j]);
			}
		}
		printf("\n");
		fprintf(file, "\n");
	}
	printf("\n");
	fprintf(file, "\n");
	fclose(file);
}

void print_board_1(m_data *data)
{
	printf("\n");
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%c ", data->board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void init_board(m_data *data)
{
	int use_arr[9] = {0};

	srand(time(NULL));

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			data->board[i][j] = '0' + rand() % 9 + 1;
			while (use_arr[data->board[i][j] - '0' - 1] == 1)
				data->board[i][j] = '0' + rand() % 9 + 1;
			use_arr[data->board[i][j] - '0' - 1] = 1;
		}
	}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (data->board[i][j] == '9')
				data->board[i][j] = '_';
}

// The algorithm is taken from internet.
// https://www.cs.princeton.edu/courses/archive/spr13/cos226/assignments/8puzzle.html
// I have modified it to fit my code.
int isSolvable(char board[][3]) // Check if the board is solvable
{
	int inv_count = 0;
	char one_dimension[9];
	int index = 0;

	// The 2D board into a 1D array
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			one_dimension[index++] = board[i][j];
	}

	// Count inversions
	for (int i = 0; i < 9; i++)
	{
		if (one_dimension[i] == '_')
			continue;
		for (int j = i + 1; j < 9; j++)
		{
			if (one_dimension[j] == '_')
				continue;
			if (one_dimension[i] > one_dimension[j])
				inv_count++;
		}
	}
	// '1' is solvable, '0' is not solvable
	return inv_count % 2 == 0;
}

void print_finish(int moves, int score, int flag)
{
	if (flag == 1)
		printf("Congratulations! You finished the game.\n\nTotal number of moves: %d\nYour Score: %d\n\n", moves, score);
	if (flag == 0)
		printf("Unfortunately! You failed to finish the game.\n\nTotal number of moves: %d\nYour Score: %d\n\n", moves, score);
}

int check_board(m_data *data)
{ // to check if board is solved
	int count = 1;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == 2 && j == 2) break; // last element is '_'
			if (data->board[i][j] != count + '0') return (0); // if element is not in order
			count++;
		}
	}
	return (1);
}

void best_score_check(int score)
{ // to check best score
	FILE *file;
	int best_score = 0;
	char str[100];

	file = fopen(BEST, "r");
	if (fscanf(file, "%[^'\n']", str) == -1)
	{
		file = fopen(BEST, "w");
		fprintf(file, "The best score is %d", score);
		fclose(file);
		return;
	}
	fclose(file);
	file = fopen(BEST, "r");
	for (int i = 0; i < 5; i++)
		fscanf(file, "%s", str);
	best_score = atoi(str);
	if (score > best_score)
	{
		file = fopen(BEST, "w");
		fprintf(file, "The best score is %d", score);
		fclose(file);
	}
}

void clear_file(char *file_name)
{
	FILE *file = fopen(file_name, "w+");
	fclose(file);
}

void play_game_pc(m_data *data)
{
	int		moves = 0;
	int		tail = 0;

	init_board(data);
	while (isSolvable(data->board) == 0) init_board(data);
	clear_file(PC);
	print_board(data, PC);
	auto_finish(data, -2, -2, &moves); // -2's are flag for the first move
	while (check_board(data) == 0)
	{
		moves++;
		tail++;
		auto_finish(data, -2, -2, &moves);
	}
	printf("Total number of computer moves: %d\n", moves - tail);
}

void	assign_letter(char letter[2], int random_letter)
{
	if (random_letter == 0) letter[0] = 'U';
	if (random_letter == 1) letter[0] = 'D';
	if (random_letter == 2) letter[0] = 'L';
	if (random_letter == 3) letter[0] = 'R';
	letter[1] = '\0';
}

int assign_last_move(int random_letter)
{
	if (random_letter == 0) return (1);
	if (random_letter == 1) return (0);
	if (random_letter == 2) return (3);
	if (random_letter == 3) return (2);
	return (-1);
}

void auto_finish(m_data *data, int last_letter, int last_move, int *moves)
{
	int		random_letter, random_move;
	char	letter[2];

	if (check_board(data) == 1) return;  // check if board is solved
	if ((*moves) % 50000 == 0) return; // to prevent infinite loop segmentation fault
	random_letter = rand() % 4; // random letter
	random_move = (rand() % 8) + 1; // random move
	assign_letter(letter, random_letter);
	while ((random_letter == last_letter && random_move == last_move) || move(data, random_move, letter, moves) == 0) // valid move check and last move check
	{
		random_letter = rand() % 4;
		random_move = (rand() % 8) + 1;
		assign_letter(letter, random_letter);
	}
	printf("Computer Move: %d-%s\n", random_move, letter); // print computer move
	print_board(data, PC); // print new_board
	random_letter = assign_last_move(random_letter); // assign last move
	auto_finish(data, random_letter, random_move, moves); // recursive function
}

void print_menu(void)
{
	printf("Welcome to the 8-Puzzle Game!\n");
	printf("1. Play the game as a user\n");
	printf("2. Play the game with PC\n");
	printf("3. Show the best score\n");
	printf("4. Exit\n >> ");
}
