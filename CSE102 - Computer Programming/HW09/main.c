#include "util.h"

/*
	Part 4. Main function
	You have to write a main function that calls the init_board() function to initialize the board and retrieves
	the board. Then, the board is passed to the play() function to start the game. You don't need to create a
	menu for this homework; the game should start automatically when the program runs
*/

int main(){
	Block ***board;

	srand(time(NULL));
	board = init_board();
	play(board);
	return (0);
}
