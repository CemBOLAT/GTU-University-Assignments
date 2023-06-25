#include "util.h"

/*
	Part 1. Initialize The Board
	This part should be implemented in the  init_board() function. This function generates and returns the
	game board, which is a 3D dynamic array of type Block. The board consists of 10 rows and 10 columns,
	with the possibility of having nested blocks in each cell. Therefore, the cells should be implemented using
	dynamic arrays of Block. The board needs to be initialized in such a way that each cell contains an empty
	block. Finally, randomly change the type of two blocks on the board to create one obstacle and one bait.
	Avoid placing them on the top-left block where the snake will start.
*/

Block ***init_board(void)
{
	Block ***board; // 3D array of Block
	int row, col;		// row index and column index
	int height;		// height of the obstacle

	board = (Block ***)malloc(sizeof(Block **) * BOARD_SIZE);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[i] = (Block **)malloc(sizeof(Block *) * BOARD_SIZE);
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = (Block *)malloc(sizeof(Block) * BOARD_SIZE);
			board[i][j]->type = EMPTY_TYPE;
			board[i][j]->value = 0;
		}
	}

	do
	{
		row = rand() % BOARD_SIZE;	// random row index for bait
		col = rand() % BOARD_SIZE;	// random column index for bait
	} while (row == 0 && col == 0); // avoid placing bait on the top-left block where the snake will start

	board[col][row][0].type = BAIT_TYPE;

	do
	{
		row = rand() % BOARD_SIZE; // random row index for obstacle
		col = rand() % BOARD_SIZE; // random column index for obstacle
	} while ((board[col][row][0].type != EMPTY_TYPE || (row == 0 && col == 0)));
	// avoid placing obstacle on the top-left block where the snake will start and on the same block as the bait

	board[col][row][0].type = OBSTACLE_TYPE;
	height = (rand() % 9) + 1; // random height of the obstacle
	board[col][row][0].value = height;
	return (board);
}
