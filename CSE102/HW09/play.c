#include "util.h"

/*
	play(): This is the main function for game play. It takes the initialized board as input and does not return
	anything. The function initializes the snake with a length of 1 block at the top-left of the board. It asks
	the user  for a new move  until the game  is over and draws the board using the draw_board()  function
	before each move. After each move, the current state of the game is checked using the check_status()
	function.  If  the  game  is  not  over  in  the  current  state,  then  the  board  and  snake  are  updated  in  the
	update() function.
*/

void play(Block ***block)
{
	Point	*snake = NULL;
	int		snake_len = 1;

	snake = (Point *)malloc(sizeof(Point) * 1);
	snake->row = 0;
	snake->col = 0;

	while (1)
	{
		draw_board(block, snake, snake_len);
		move(snake, snake_len);
		if (check_status(block, snake, snake_len))
			break;
		snake = update(snake, block, &snake_len);
	}
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
			free(block[i][j]);
		free(block[i]);
	}
	free(block);
	free(snake);
	return;
}

/*
	move(): This function takes the snake as input and applies the next move obtained from the user. The
	next move should be obtained from the user within this function, and the head of the snake should be
	set  to  its  next  position  based  on  the  given  direction.  The  snake  can  turn  in  one  of  the  four  directions
	except the direction that goes through its own body. If the user tries to make such a move, it should be
	ignored.
*/

void move(Point *snake, int snake_len)
{
	FILE *fp = fopen(TEMP_FILE_NAME, "w");
	int size = sizeof(snake) / sizeof(Point);
	int flag = 0;
	char input;
	int row_diff = 0, col_diff = 0;

	while (row_diff == 0 && col_diff == 0)
	{
		flag = 0;
		printf("Next Move 'w' (up) 'a' (left) 's' (down) 'd' (right)\n >> ");
		scanf(" %c", &input);

		if (input == 'w')
		{
			if (!(snake_len > 1 && (snake[0].col - 1 == snake[1].col)))
			{
				col_diff = -1;
				flag = 1;
			}
		}
		else if (input == 'a')
		{
			if (!(snake_len > 1 && snake[0].row - 1 == snake[1].row))
			{
				row_diff = -1;
				flag = 1;
			}
		}
		else if (input == 's')
		{
			if (!(snake_len > 1 && (snake[0].col + 1 == snake[1].col)))
			{
				col_diff = 1;
				flag = 1;
			}
		}
		else if (input == 'd')
		{
			if (!(snake_len > 1 && (snake[0].row + 1 == snake[1].row)))
			{
				row_diff = 1;
				flag = 1;
			}
		}
		if (flag == 0)
			printf("Wrong Input\n");
	}

	snake[0].row += row_diff;
	snake[0].col += col_diff;
	// I am saving the input to a file because it is imposible to pass the user input to the update function without returning input from the move function.
	fprintf(fp, "%d %d", row_diff, col_diff);
	fclose(fp);
}

/*
	check_status():  After  the move  is made,  the  consequences  of  the  last  move  need  to  be  checked.  This
	function takes the snake and the board as input and returns 1 if the game is over, otherwise it returns 0.
	In this function, three conditions need to be checked:
	1. Does the head of the snake hit its own body?
	2. Does the snake collide with the wall?
	3. Does the snake encounter an obstacle that has x number of blocks, where x is greater than the
	length of the snake?
	The game is over if any of these conditions are met, so the function returns 1 in that case.
*/

int check_status(Block ***board, Point *snake, int snake_len)
{
	int index = 1;

	if (snake->row < 0 || snake->row >= BOARD_SIZE || snake->col < 0 || snake->col >= BOARD_SIZE) // check if snake is out of board
		return (printf("Game Over >> Your sneak crushed to wall\n"), 1);
	while (index < snake_len)
	{
		if (snake[index].row == snake->row && snake[index].col == snake->col && (index != snake_len - 1)) // check if snake hit itself
			return (printf("Game Over >> Your sneak crushed to itself\n"), 1);
		index++;
	}
	if (board[snake->col][snake->row]->type == OBSTACLE_TYPE && board[snake->col][snake->row]->value > snake_len) // check if snake hit obstacle
		return (printf("Game Over >> Your sneak crushed to obstacle\n"), 1);
	return (0);
}

/*
	update():  If  the  game  is  not  over,  the  play()  function  calls  the  update()  function.  In  this  function,  the
	program updates the coordinates of the snake's body, considering whether the snake ate a bait in the
	last move or not. Then, the function updates the bait and obstacles on the board. If the snake ate a bait
	in  the  last  move,  the  length  of  the  snake  is  increased  by one  block. Otherwise, the  rest  of  the  body  is
	shifted to keep the body and head connected. There can be only one bait at a time on the board. This
	function  also  updates  the  obstacles  every 5 moves.  The  obstacles  appear  randomly on  the  board,  and
	there can be a maximum of 3 obstacles at a time. Additionally, the height of obstacles can be increased
	by adding new obstacle blocks on top of existing ones. If the snake encounters an obstacle that is shorter
	than  its  body,  it  can  capture  the  block  by  destroying the  obstacle. This  is  done  by  deleting the  nested
	blocks on the obstacle, setting the block type to empty, and the value to 0. Note that neither obstacles
	nor bait can appear in blocks that are currently occupied by the snake.
*/

Point *update(Point *snake, Block ***board, int *snake_len)
{
	static int move_count = 0;
	int obs_count = 0;
	int row_diff, col_diff;
	int temp_row, temp_col;
	FILE *fp = fopen(TEMP_FILE_NAME, "r");

	move_count++;
	fscanf(fp, "%d %d", &row_diff, &col_diff); // read the last move from the file
	fclose(fp);

	temp_row = snake[0].row - row_diff;
	temp_col = snake[0].col - col_diff;
	if (*snake_len > 1) // if snake is longer than 1 block, shift the body
	{
		for (int i = 1; i < *snake_len; i++)
		{
			int temp_row2 = snake[i].row;
			int temp_col2 = snake[i].col;
			snake[i].row = temp_row;
			snake[i].col = temp_col;
			temp_row = temp_row2;
			temp_col = temp_col2;
		}
	}
	if (board[snake[0].col][snake[0].row]->type == BAIT_TYPE) // if snake ate a bait
	{
		int new_bait_row, new_bait_col;
		int is_empty = 0, is_empty2 = 1;

		(*snake_len)++; // increase snake length
		snake = (Point *)realloc(snake, sizeof(Point) * (*snake_len)); // reallocate memory for the new block
		snake[*snake_len - 1].row = temp_row;
		snake[*snake_len - 1].col = temp_col;

		board[snake[0].col][snake[0].row]->type = EMPTY_TYPE; // delete the bait
		do {
			is_empty = 0;
			is_empty2 = 1;
			new_bait_col = rand() % BOARD_SIZE; // generate new bait
			new_bait_row = rand() % BOARD_SIZE;
			if (board[new_bait_col][new_bait_row]->type == EMPTY_TYPE)
				is_empty = 1;
			for (int j = 0; j < *snake_len; j++)
			{
				if (snake[j].row == new_bait_row && snake[j].col == new_bait_col)
				{
					is_empty2 = 0;
					break;
				}
			}
		} while (is_empty == 0 || is_empty2 == 0);

		board[new_bait_col][new_bait_row]->type = BAIT_TYPE; // place the new bait
	}
	else if (board[snake[0].col][snake[0].row]->type == OBSTACLE_TYPE)	// when the snake hiys an obstacle it has to be deleted because it is shorter than the snake
	{																	// if the snake hits an obstacle that is longer than the snake,
		board[snake[0].col][snake[0].row]->type = EMPTY_TYPE;			// the game is over as checked in the check_status function
		board[snake[0].col][snake[0].row]->value = 0;
	}
	if (move_count % 5 == 0) // update obstacles every 5 moves
	{
		// count obstacles
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (board[i][j]->type == OBSTACLE_TYPE)
					obs_count++;
			}
		}
		if (obs_count < 3) // if there are less than 3 obstacles, generate a new one
		{
			int new_obs_row, new_obs_col;
			int is_empty = 0, is_empty2 = 1;
			do
			{
				is_empty = 0;
				is_empty2 = 1;
				new_obs_col = rand() % BOARD_SIZE; // generate new bait
				new_obs_row = rand() % BOARD_SIZE;
				if (board[new_obs_col][new_obs_row]->type == EMPTY_TYPE)
					is_empty = 1;
				for (int j = 0; j < *snake_len; j++)
				{
					if (snake[j].row == new_obs_row && snake[j].col == new_obs_col)
					{
						is_empty2 = 0;
						break;
					}
				}
			} while (is_empty == 0 || is_empty2 == 0);
			if (board[new_obs_col][new_obs_row]->type == OBSTACLE_TYPE) // if there is already an obstacle, add a random value to it
			{
				int add_val = rand() % 9 + 1; // add a random value to the obstacle
				board[new_obs_col][new_obs_row]->value += add_val;
				if (board[new_obs_col][new_obs_row]->value > 9) // if the value is greater than 9, set it to 9
					board[new_obs_col][new_obs_row]->value = 9;
			}
			else
			{
				board[new_obs_col][new_obs_row]->type = OBSTACLE_TYPE; // place the new obstacle
				board[new_obs_col][new_obs_row]->value = rand() % 9 + 1; // add a random value to the obstacle
			}
		}
		else if (obs_count == 3) // if there are 3 obstacles, add a random value to one of them
		{

			int **obs = (int **)malloc(sizeof(int *) * 3); // array to store the coordinates of the obstacles
			int add_obs, sel_obs, index = 0;

			for (int i = 0; i < 3; i++) // allocate memory for the array
				obs[i] = (int *)malloc(sizeof(int) * 2);
			// store the coordinates of the obstacles
			for (int i = 0; i < BOARD_SIZE; i++)
			{
				for (int j = 0; j < BOARD_SIZE; j++)
				{
					if (board[i][j]->type == OBSTACLE_TYPE)
					{
						obs[index][0] = i;
						obs[index][1] = j;
						index++;
					}
				}
			}
			add_obs = (rand() % 9) + 1; // add a random value to the obstacle
			sel_obs = rand() % 3; // select a random obstacle
			board[obs[sel_obs][0]][obs[sel_obs][1]]->value += add_obs; // add the value to the obstacle
			if (board[obs[sel_obs][0]][obs[sel_obs][1]]->value > 9) // if the value is greater than 9, set it to 9
				board[obs[sel_obs][0]][obs[sel_obs][1]]->value = 9;

			for (int i = 0; i < 3; i++) // free the memory
			{
				free(obs[i]);
			}
			free(obs);
		}
	}
	return (snake);
}
