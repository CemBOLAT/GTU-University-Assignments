# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define MENU_SIZE 14
# define MENU_FILE_NAME "./menu.txt"
# define BILL_FILE_NAME "./bill.txt"
# define SCHOOL_NUMBER 210104004010
# define ALIGNMENT 8

void	f_draw_line(void);
void	print_banner(void);
void	part1(void);
void	part2(void);

int main(void)
{
	print_banner();
	part1();
	part2();
}

//======================================part1 starts======================================//
// printing menu to terminal from getting infos from menu.txt
void			f_print_menu(void);
/*
	prints bills first 4 columns to bill.txt file
	for ex:
		210104004010	    06.04.2023/23:54
		------------------------------------
		 Product		Price(TL)
		------------------------------------
*/
void			f_print_start_of_bill(void);
/*
	last question after getting '0' input from user
*/
int				ask_last_question(double total_price, int ordered);
/*
	returning the total price of selected menu item to update total price
*/
static double	f_new_total_price(int choose, int quantity, int ordered);
/*
	discount options
*/
static double	apply_discount(double total_price, FILE *bill, char are_you_student);
/*
	printing end of bill to bill.txt file
	for ex:
	 Total:						200.00
	 Additional discount:	   -20.00
	------------------------------------
	 Price :					180.00
	 Price + VAT:				212.40
*/
void			print_end_of_bill(double total_price, char are_you_student, int ordered);
/*
	prints bill to terminal
*/
void			print_full_of_bill();
int				find_digit(int nbr);

void part1(void)
{
	int finish_serving = 1;
	int choose;
	int quantity;
	double total_price = 0;
	int ordered = 0;

	printf("\033[35mTODO : This  program  will  create  a  menu  and  calculate  the  prices  for  the  dishes  that  users  choose.\033[0m\n");
	f_draw_line();
	f_print_menu();
	f_print_start_of_bill();
	while (finish_serving == 1)
	{
		printf("\033[33mPlease choose a product (1-%d): \033[0m", MENU_SIZE);
		scanf("%d", &choose);
		while (choose < 0 || choose > MENU_SIZE)
		{
			printf("\033[31mINVALID INPUT ! \n\033[0m");
			printf("\033[33mPlease choose a product (1-%d): \033[0m", MENU_SIZE);
			scanf("%d", &choose);
		}
		if (choose == 0) // asking last student question !
			finish_serving = ask_last_question(total_price, ordered + 1);
		else
		{
			printf("\033[33mHow many servings do you want ? : \033[0m");
			scanf("%d", &quantity);
			while (quantity < 0)
			{
				printf("\033[31mINVALID INPUT ! \n");
				printf("\033[33mHow many servings do you want ? : \033[0m");
				scanf("%d", &quantity);
			}
			if (quantity == 0) // asking last student question !
				finish_serving = ask_last_question(total_price, ordered + 1);
			else
			{
				ordered++;
				total_price += f_new_total_price(choose, quantity, ordered);
			}
		}
	}
	f_draw_line();
}

void f_print_menu(void)
{
	char letter;
	int i = 1;
	FILE *file_stream;
	double price;

	file_stream = fopen(MENU_FILE_NAME, "r");
	printf("Yemek Listesi: \n");
	printf("\033[34m===========\n\033[0m");

	while (fscanf(file_stream, "%c", &letter) && letter != '\n'); // ignoring first menu line >>PRODUCT PRICE(TL)<<
	printf("%*d. ", ((MENU_SIZE / 10) + 1),i); // aligning the menu orders
	/*
		for ex:
			  1...
			 10...
		    100.
	*/
	fscanf(file_stream, "%c", &letter);
	while (1)
	{
		printf("%c", letter);
		if (letter == '\t')
		{
			while (letter != '\n')
				fscanf(file_stream, "%c", &letter);
			printf("\n");
			if (i == MENU_SIZE)
				break;
			printf("%*d. ", ((MENU_SIZE / 10) + 1), ++i); // aligning the menu orders
		}
		fscanf(file_stream, "%c", &letter);
	}
	printf("\033[34m===============================\n\033[0m");
	fclose(file_stream);
}

void f_print_start_of_bill(void)
{
	FILE	*bill;
	char	str[80];
	struct tm	*time_struct;
	time_t		real_time;

	time(&real_time);
	time_struct = localtime( &real_time );
	bill = fopen(BILL_FILE_NAME, "w+");
	strftime(str,80,"%d.%m.%Y/%H:%M", time_struct);
	fprintf(bill, "%li\t%*s\n\n", SCHOOL_NUMBER, 20,str);
	fprintf(bill, "------------------------------------\n\n");
	fprintf(bill, " Product                Price (TL)\n\n");
	fprintf(bill, "------------------------------------\n\n");
	fclose(bill);
}

int	ask_last_question(double total_price, int ordered)
{
	char are_you_student;

	while (getchar() != '\n'); // clearing buffer
	printf("\033[32mAre you student? (Y/N): \033[0m");
	scanf("%c", &are_you_student);
	while (are_you_student != 'Y' && are_you_student != 'N')
	{
		while (getchar() != '\n');
		printf("\033[33mINVALID INPUT !\n\033[0m");
		printf("\033[32mAre you student? (Y/N): \033[0m");
		scanf("%c", &are_you_student);
	}
	print_end_of_bill(total_price, are_you_student, ordered);
	print_full_of_bill();
	return (0);
}

static double f_new_total_price(int choose, int quantity, int ordered)
{
	FILE *menu;
	FILE *bill;
	int i = 0;
	char letter;
	double addition;
	int	len = 0;
	menu = fopen(MENU_FILE_NAME, "r+");
	bill = fopen(BILL_FILE_NAME, "r+");

	while (fscanf(menu, "%c", &letter) && letter != '\n');
	/*
		2 times ordered because every item comes with '\n'
		+7 becuase top of bill has 7 lines

		Pilav                     30.00

		Salata                    45.50

		Lahmacun                  55.60

	 	Total :                  131.10
	*/
	while (i != (2 * ordered) + 7)
	{
		fscanf(bill, "%c", &letter);
		if (letter == '\n')
			i++;
	}
	if (quantity != 1) // printing quantity << 1 has special rules >>
		fprintf(bill, " %d*", quantity);
	i = 0;
	while (1)
	{
		if (i + 1 == choose)
		{
			fprintf(bill, " ");
			while (fscanf(menu, "%c", &letter) != -1 && letter != '\t')
			{
				fprintf(bill, "%c", letter);
				len++; // counting item length
			}
			fscanf(menu, "%lf", &addition);
			if (quantity != 1) // << 1 has special rules >>
				for (int i = 0; i < 31 - (len + find_digit((int)(addition * quantity)) + find_digit(quantity) + 5); i++)
					fprintf(bill, " ");
			else // world len - total digit of item money (integer part + 3)
				for (int i = 0; i < 31 - (len + find_digit((int)(addition * quantity)) + 3); i++)
					fprintf(bill, " ");
			fprintf(bill, "%.2lf\n\n", addition * quantity);
			break;
		}
		fscanf(menu, "%c", &letter);
		if (letter == '\n')
			i++;
	}
	addition *= quantity;
	fclose(menu);
	fclose(bill);
	return (addition);
}

void print_end_of_bill(double total_price, char are_you_student, int ordered)
{
	FILE *bill;
	int i = 0;
	char letter;
	double addition;
	bill = fopen(BILL_FILE_NAME, "r+");

	while (i != (2*ordered) + 7)
	{
		fscanf(bill, "%c", &letter);
		if (letter == '\n')
			i++;
	}
	fprintf(bill, " Total :%*.2lf\n\n",24, total_price);
	total_price = apply_discount(total_price, bill, are_you_student);
	fprintf(bill, "------------------------------------\n\n");
	fprintf(bill, " Price :%*.2lf\n\n",24, total_price);
	fprintf(bill, " Price + VAT :%*.2lf\n\n",18, (total_price * 118) / 100);
	fclose(bill);
}

static double apply_discount(double total_price, FILE *bill, char are_you_student)
{
	double	copy = total_price;
	if (are_you_student == 'Y')
	{
		fprintf(bill, " Student discount:%*.2lf\n\n", 14, -((total_price * 125) / 1000));
		copy -= (copy * 12.5) / 100;
	}
	if (total_price >= 150)
	{
		fprintf(bill, " Additional discount:%*.2lf\n\n", 11,-((total_price * 10) / 100));
		copy -= (copy * 10) / 100;
	}
	return ((copy));
}

void			print_full_of_bill()
{
	FILE	*bill;
	char	letter;

	bill = fopen(BILL_FILE_NAME, "r+");
	f_draw_line();
	while (fscanf(bill, "%c", &letter) != -1)
		printf("%c", letter);
	fclose(bill);
}

int find_digit(int nbr)
{
	int	res = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 10;
		res++;
	}
	return (res);
}

//======================================part1 ends======================================//
//======================================part2 starts====================================//

void print_result(int user, int program);

void part2(void)
{
	int user_choice, program_choice;
	char new_game_choice;
	int is_game_over = 1;

	srand(time(NULL));
	printf("\033[35mTODO : Write a rock paper scissors game\033[0m\n");
	f_draw_line();
	while (is_game_over)
	{
		while(getchar() != '\n');
		printf("\033[36mPlease make a choice !\n1: Stone, 2: Paper, 3: Scissors : \033[0m");
		scanf("%d", &user_choice);
		while (user_choice < 1 || user_choice > 3)
		{
			printf("\033[33mInvalid Input !\033[0m\n");
			printf("\033[36mPlease make a choice !\n1: Stone, 2: Paper, 3: Scissors : \033[0m");
			scanf("%d", &user_choice);
		}
		program_choice = (rand() % 3) + 1;
		print_result(user_choice, program_choice);
		while (getchar() != '\n')
			;
		printf("Do you want to play again? (Y/N): ");
		scanf("%c", &new_game_choice);
		while (new_game_choice != 'Y' && new_game_choice != 'N')
		{
			while (getchar() != '\n');
			printf("\033[32mInvalid Input !\033[0m\n");
			printf("Do you want to play again? (Y/N): ");
			scanf("%c", &new_game_choice);
		}
		if (new_game_choice == 'N')
			is_game_over = 0;
	}
	f_draw_line();
}

void print_result(int user, int program)
{
	if (user == program)
	{
		if (user == 1)
			printf("You chose Stone. I chose Stone. It's a tie!");
		else if (user == 2)
			printf("You chose Paper. I chose Paper. It's a tie!");
		else if (user == 3)
			printf("You chose Scissors. I chose Scissors. It's a tie!");
	}
	else if (user == 1)
	{
		if (program == 3)
			printf("You chose Stone. I chose Scissors. You won!");
		else if (program == 2)
			printf("You chose Stone. I chose Paper. I won!");
	}
	else if (user == 2)
	{
		if (program == 3)
			printf("You chose Paper. I chose Scissors. I won!");
		else if (program == 1)
			printf("You chose Paper. I chose Stone. You won!");
	}
	else if (user == 3)
	{
		if (program == 1)
			printf("You chose Scissors. I chose Stone. I won!");
		else if (program == 2)
			printf("You chose Scissors. I chose Paper. You won!");
	}
	printf("\n");
}
//=====================================part2 ends===========================
//=====================================util starts==========================

/* printing blue lines to increase visibility */
void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}

/* printing homework banner to increase visibility */
void print_banner(void)
{
	f_draw_line();
	printf("\n\033[32m \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >======>     >=>   >=>\n \
	>=>    >=>   >=>    >=>   >> >=>   >>=> >=>       >=>        >=>   >=>    >=>   >=>    >=>   >=>  >=>               >=>          >=>\n \
	>=>    >=> >=>        >=> >=> >=> > >=> >=>       >=>   >>   >=> >=>        >=> >=>    >=>   >=> >=>              >=>  >=>      >>=>\n \
	>=====>>=> >=>        >=> >=>  >=>  >=> >=====>   >=>  >=>   >=> >=>        >=> >> >==>      >>=>>       >====> >=>     >=>    > >=>\n \
	>=>    >=> >=>        >=> >=>   >>  >=> >=>       >=> >> >=> >=> >=>        >=> >=>  >=>     >=>  >=>           >=>      >=>  >=> >=> \n \
	>=>    >=>   >=>     >=>  >=>       >=> >=>       >> >>    >===>   >=>     >=>  >=>    >=>   >=>   >=>           >=>    >=>  >===>>=>>=> \n \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >=>      >=> >=>     >=>           >==>      	  >=>\n \
	\t\t\t\t\t CEMAL BOLAT 210104004010 \033[0m\n\n");
	f_draw_line();
}
//=========================================util ends================================
