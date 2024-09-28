# include <stdio.h>
# include <stdlib.h>
# include <time.h>

/*
	These moves should be defined at the beginning of the codewith  direction  names  as  the  keys.
	Any  control  or  selection  with  [a,  d,  w,  s]  characters will  result  in  a missgrading.
	I defined my keys as a macro because pdf has 'define' keyword.
*/
# define UP 'w'
# define DOWN 's'
# define LEFT 'a'
# define RIGHT 'd'

/*

	Firstly my program prints the introduction (banner welcome message...) part with f_print_entrance() function
	for ex:
		Welcome to the 2D puzzle game
		1. New Game...
	then takes input from user (f_conditions()) 1 2 3 other ones aren't valid program prints errors to user.
	1 --> starts new_game in new_game() function
	2 --> prints help booklet in f_print_help() function
	3 --> terminates the program by changing the value of is_game_finished variable to 0
*/

// print_menu
void	f_print_entrance(void);
// taking input and implement the operation
int		f_conditions(void);
// printing help booklet
void	f_print_help(void);
// printing ************** blue line
void	f_print_divider(void);
// printing HOMEWORK 03 BANNER
void	print_banner(void);

int main(void)
{
	int	is_game_finished = 1;

	print_banner();
	printf("\033[36mWelcome to the 2D puzzle game !\n\033[0m");
	while (is_game_finished)
	{
		f_print_entrance();
		is_game_finished = f_conditions(); // f_conditions part4
	}
}

/*
	p_x : player_x;
	p_y : player_y;
	d_x : door_x;
	d_y : door_y;
*/

/*
	f_draw_room() function draws room with f_draw_line() and f_draw_inside() functions.
*/

void f_draw_room(int size, int d_x, int d_y, int p_x, int p_y);
void f_draw_line(int size);
void f_draw_inside(int size, int d_x, int d_y, int p_x, int p_y);
//			gameplay part
void f_gameplay(int size, int d_x, int d_y, int p_x, int p_y);
/*
	check the move is valid or not
*/
static int f_check_valid_move(int size, int p_x, int p_y, int x_change, int y_change);

/*
	drawing room:
	for ex: size equal to 5;
	0 represents ' ' to increase visibilty
=============================================
	-----x-----
	 0 1 2 3 4
	-----------		-->> ((size * 2) + 1) times printing '-'
 0| |0|0|0|0|0|		take a random number then take its mod to (size * size)
 1|	|0|0|0|0|0|		for ex: 23 is our random number for 'door' and 15 for 'player'
 2y	|0|0|0|0|0|		23 / 5(size) = 4	15 / 5(size) = 3
 3|	|C|0|0|0|0|		23 % 5(size) = 3	15 % 5(size) = 0
 4|	|0|0|0|D|0|		3 is our x coordinate and 4 is our y coordinate for 'door'
	-----------		0 is our x coordinate and 3 is our y coordinate for 'player'
==============================================
*/

void f_newgame(void) //
{
	int door, door_x, door_y;
	int player, player_x, player_y;
	int size;

	printf("\033[35mPlease enter room size << between 5 - 10 (inclusive) >> : \033[0m");
	scanf("%d", &size);
	while (size > 10 || size < 5)
	{
		printf("\033[31mInvalid input !\n\033[0m");
		printf("\033[35mPlease enter room size << between 5 - 10 (inclusive) >> : \033[0m");
		scanf("%d", &size);
	}
	srand(time(NULL));
	door = rand() % (size * size);
	player = rand() % (size * size);
	while (player == door)
		player = rand() % (size * size);
	/*
		assinging x and y coordinates.
	*/
	door_x = door % size;
	door_y = door / size;
	player_x = player % size;
	player_y = player / size;
	f_draw_room(size, door_x, door_y, player_x, player_y);
	f_gameplay(size, door_x, door_y, player_x, player_y);
}

void f_draw_room(int size, int d_x, int d_y, int p_x, int p_y) // part1
{
	f_draw_line(size * 2 + 1);
	f_draw_inside(size, d_x, d_y, p_x, p_y);
	f_draw_line(size * 2 + 1);
}

void f_draw_line(int size)
{
	for (int i = 0; i < size; i++)
		printf("-");
	printf("\n");
}

/*

	size 5:
		----x------
		 0 1 2 3 4
		----------- << used '0' instead of ' ' to increase visibility >>
	0|	|0|0|0|0|0| I printed grouped "|0" and print '|' at the end
	1|	|0|0|0|0|0|
	2y	|0|0|0|0|0|
	3|	|C|0|0|0|0|
	4|	|0|0|0|D|0|
*/

void f_draw_inside(int size, int d_x, int d_y, int p_x, int p_y)
{
	for (int i = 0; i < size; i++) // y coordinate
	{
		for (int j = 0; j < size; j++) // x coordinate
		{
			if (d_x == j && d_y == i)
				printf("|D");
			else if (p_x == j && p_y == i)
				printf("|C");
			else
				printf("| ");
		}
		printf("|\n");
	}
}

void f_gameplay(int size, int d_x, int d_y, int p_x, int p_y) // part2
{
	char move;			 // 'w' , 's', 'a', 'd'
	int is_finished = 1; // it is our boolean value to check is the game finished or not << 0 means finished >>
	int x_change, y_change, move_counter = 0;

	while (is_finished)
	{
		x_change = 0;
		y_change = 0;
		while (getchar() != '\n');
		printf("Next-move : ");
		scanf("%c", &move);
		/* moves effect*/
		while (!(move == UP || move == DOWN || move == RIGHT || move == LEFT))
		{
			printf("\033[31mInvalid input << w a s d >> \n\033[0m");
			while (getchar() != '\n');
			printf("Next-move : ");
			scanf("%c", &move);
		}
		// assinging x's and y's changes
		switch (move)
		{
		case UP:
			y_change = -1; // it goes "up" and decrease "y" value according the room << line 120 >>
			break;
		case LEFT:
			x_change = -1; // it goes "left" and decrease "x" value according the room << line 120 >>
			break;
		case DOWN: // it goes "down" and increase "y" value according the room << line 120 >>
			y_change = 1;
			break;
		case RIGHT: // it goes "right" and increase "x" value according the room << line 120 >>
			x_change = 1;
			break;
		}
		if (p_x + x_change == d_x &&
			p_y + y_change == d_y) //  check did the player reach the door after last move
		{
			is_finished = 0;
			move_counter++;
			printf("\033[32mCongartz ! << You have finished in %d moves >>\n\033[0m", move_counter); // no more print after reaching door
			return;
		}
		else if (f_check_valid_move(size, p_x, p_y, x_change, y_change)) // check the move's valibility
		{
			p_x += x_change;
			p_y += y_change;
			move_counter++;
			f_draw_room(size, d_x, d_y, p_x, p_y); // redraw the room after changes
		}
		else
			printf("\033[31mInvalid Move << Character cannot escape from the room. >> \n\033[0m");
	}
}

static int f_check_valid_move(int size, int p_x, int p_y, int x_change, int y_change) // part3
{
	if (p_x + x_change < size && p_x + x_change >= 0 &&
		p_y + y_change < size && p_y + y_change >= 0)
		return (1);
	return (0);
}

void	f_print_entrance(void)
{
	printf("\033[33m");
	printf("1. New Game\n");
	printf("2. Help\n");
	printf("3. Exit\n >> ");
	printf("\033[0m");
}

int	f_conditions(void)
{
	int input;

	scanf("%d", &input);
	while (input != 1 && input != 2 && input != 3)
	{
		printf("\033[31mInvalid Input !\n\033[0m");
		f_print_entrance();
		scanf("%d", &input);
	}
	switch (input)
	{
	case 1:
		f_print_divider();
		f_newgame();
		f_print_divider();
		return (1);
		break;
	case 2:
		f_print_divider();
		f_print_help();
		f_print_divider();
		return (1);
		break;
	case 3:
		printf("\033[32mHave a nice day GOODBYE !\n\033[0m");
		f_print_divider();
		return (0);
		break;
	}
}

/*
	Taken from pdf as teacher recommended.
*/
void f_print_help()
{
	printf("\n\t\033[35mThe character is able to move one space in any of the four cardinal directions: up, down, left, and right.\n\
	Diagonal moves are not allowed. \n\
	The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down. \n\
	The game will prompt the user for a new move after each move is made until the game is over.\n\n\033[0m");
	return;
}

/* printing blue lines to increase visibility */
void f_print_divider()
{
	printf("\033[34m***************************************\n\033[0m");
}

/* printing homework banner to increase visibility */
void print_banner(void)
{
	f_print_divider();
	printf("\n\033[32m \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >======>     >=>   >=>\n \
	>=>    >=>   >=>    >=>   >> >=>   >>=> >=>       >=>        >=>   >=>    >=>   >=>    >=>   >=>  >=>               >=>      >=>>=>\n \
	>=>    >=> >=>        >=> >=> >=> > >=> >=>       >=>   >>   >=> >=>        >=> >=>    >=>   >=> >=>              >=>  >=>      >=>\n \
	>=====>>=> >=>        >=> >=>  >=>  >=> >=====>   >=>  >=>   >=> >=>        >=> >> >==>      >>=>>       >====> >=>     >=>   >=>\n \
	>=>    >=> >=>        >=> >=>   >>  >=> >=>       >=> >> >=> >=> >=>        >=> >=>  >=>     >=>  >=>           >=>      >=>     >=>\n \
	>=>    >=>   >=>     >=>  >=>       >=> >=>       >> >>    >===>   >=>     >=>  >=>    >=>   >=>   >=>           >=>    >=>       >=>\n \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >=>      >=> >=>     >=>           >==>      >====>\n \
	\t\t\t\t\t CEMAL BOLAT 210104004010 \033[0m\n\n");
	f_print_divider();
}
