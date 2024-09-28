#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define USER "./user.txt" // file that saves user's moves
#define PC "./pc.txt" // file that saves pc's moves
#define BEST "./best_score.txt" // file that saves best score
#define MAX_SCORE 1000 // max_score
#define DECREASE 10 // decresing that defined value after each move

typedef struct t_data
{
	char board[3][3];
} m_data;


void	print_menu(void); // print menu that pdf gave us
void	show_best_score(void); // option '3'
void	play_game(m_data *data); // option '1'
void	init_board(m_data *data); // initilize random board
void	print_board(m_data *data ,char *file_name); // printing board to terminal and given file name that I defined above
int		move(m_data *data, int input, char *letter, int *moves); // making moves with user's control
void	print_board_1(m_data *data); // printing same board to terminal after illegal move
void	print_finish(int moves, int score, int flag); // printing message to user after solving board or having no scores left
int		check_board(m_data *data); // checking the board is solved or not
void	best_score_check(int score); // cheching the user has best score or not
void	clear_file(char *file_name); // clearing given file with opening them with w+
void	play_game_pc(m_data *data); // option '2'
void	auto_finish(m_data *data, int last_letter, int last_move, int *moves); // recursive function that completes the puzzle
int		isSolvable(char board[3][3]); // checking the puzzle is solvable or not
void	print_move(m_data *board1, m_data *board2); // print move that has been made by pc after solving puzzle with comparing board

#endif
