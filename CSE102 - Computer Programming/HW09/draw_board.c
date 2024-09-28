#include "util.h"

/*
	Part 2. [20 pts] Draw The Board
	This part should be implemented in the  draw_board() function. The function takes the  game board as
	input  and  prints  it  in  the  specified  format  below.  The  function  uses  "-"  for  horizontal  lines  and  "|"  for
	vertical lines to draw the edges of the game board. When drawing the cells:
	• If the cell is of type "empty", nothing is printed.
	• If the cell is captured by the snake's body, "X" is printed.
	• If the cell is captured by the snake's head, "O" is printed.
	• If the cell is of type "bait", "." is printed.
	• If there is an obstacle in the cell, the number of nested blocks is printed.
*/

void	draw_board(Block ***board, Point *snake, int snake_len){
	int k = 0;
	int is_printed = 0; // 0: not printed, 1: printed

	printf(" ");
	for (int i = 0; i < (BOARD_SIZE * 2) - 1; i++) printf("-");
	printf("\n");
	for (int i = 0; i < BOARD_SIZE; i++){
		printf("|");
		for (int j = 0; j < BOARD_SIZE; j++){
			is_printed = 0;
			k = 0;
			if (board[i][j]->type == BAIT_TYPE) printf(". "); // bait
			else if (board[i][j]->type == OBSTACLE_TYPE) printf("%d ", board[i][j]->value); // obstacle
			else {
				while (k < snake_len){
					if (snake[k].col == i && snake[k].row == j && k == 0){ // snake head
						printf("O ");
						is_printed = 1;
						break;
					}
					else if (snake[k].col == i && snake[k].row == j){ // snake body
						printf("X ");
						is_printed = 1;
						break;
					}
					k++;
				}
				if (is_printed == 0) printf("  ");
			}
		}
		printf("\b|\n");
	}
	printf(" ");
	for (int i = 0; i < (BOARD_SIZE * 2) - 1; i++) printf("-");
	printf("\n");
}
