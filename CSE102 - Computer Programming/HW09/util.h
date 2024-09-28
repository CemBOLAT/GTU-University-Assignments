#ifndef UTIL_H
# define UTIL_H

#include "define.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
	The board consist of blocks. The block structure has two variables: type (char) and value (int). The type
	can have one of the three values: 'o' for obstacle block type, 'b' for bait block type, and 'e' for empty block
	type. The value represents the height of the obstacle, and it is zero for empty and bait blocks.
*/

typedef struct m_block{
	char	type;
	int		value;
} Block;

/*
	You are rquired to define a point structure. The snake is implemented as a dynamic array of point
	structures. The point data structure consists of two integer variables: row and col.
*/

typedef struct m_point{
	int	row;
	int	col;
} Point;


Block	***init_board(void);
void	play(Block ***block);
void	draw_board(Block ***board, Point *snake, int snake_len);
void	move(Point *snake, int snake_len);
int		check_status(Block ***board, Point * snake, int snake_len);
Point	*update(Point *snake, Block ***board, int *snake_len);

#endif
