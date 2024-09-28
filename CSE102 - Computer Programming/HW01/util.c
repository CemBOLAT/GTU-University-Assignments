#include "util.h"

// part1 has 1 auxiliary function
void	assign_small_and_big(int *s, int *b, int d1, int d2);
// part2 has no auxiliary functions

//part3 has 3 auxilary functions
static int	get_index_digit(int nbr, int i);
static int	get_digit_nbr(int nbr);
void	put_space_and_nbr(int loop, int nbr, int m);
// part4 has no auxiliary function

// =======================================PART 1 STARTS===================================================
void	part1(t_main *data)
{
	int	small, big;
	int	temp;

	printf("\n\033[33;1mTODO: Read two integers and calculate their GCD with Euclidean algorithm. \033[0m\n");
	printf("\nFirst Integer: ");
	scanf("%d",&data->data_1.nbr1); // receiving input
	while (data->data_1.nbr1 < 0) { // input control
		printf("\033[31mInvalid input ! Only positive numbers are valid !! \033[0m\n");
		printf("First Integer: ");
		scanf("%d",&data->data_1.nbr1); // receiving input
	}
	printf("Second Integer: ");
	scanf("%d",&data->data_1.nbr2); // receiving input
	while (data->data_1.nbr2 < 0) { // input control
		printf("\033[31mInvalid input ! Only positive numbers are valid !! \033[0m\n");
		printf("Second Integer: ");
		scanf("%d",&data->data_1.nbr2); // receiving input
	}
	if (data->data_1.nbr1 == 0) // checking special conditions if one number is 0 then gcd is other number
		printf("\nGCD of %d and %d is %d\n",data->data_1.nbr1,
		data->data_1.nbr2, data->data_1.nbr2);
	else if (data->data_1.nbr2 == 0)
		printf("\nGCD of %d and %d is %d\n",data->data_1.nbr1,
		data->data_1.nbr2, data->data_1.nbr1);
	else if (data->data_1.nbr2 == data->data_1.nbr1)
		printf("\nGCD of %d and %d is %d\n",data->data_1.nbr1,
		data->data_1.nbr2, data->data_1.nbr1);
	else {
		assign_small_and_big(&small, &big, data->data_1.nbr1, data->data_1.nbr2);
		/*
		Ex:
			number1 = 252
			number2 = 102
			before entering while --> 			big = 252 - small = 102
			-- after first entry to while -->  	big = 102 - small =  48 which is 252 % 102
			before second entry to while -->   	big = 102 - small =  48
			-- after second entry to while -->  big =  48 - small =   6 which is 102 %  48
			>>> no mone entry to while because 48 % 6 == 0 --> 6 is these numbers GCD <<<
		*/
		while (big % small != 0) {
			temp = small;
			small = big % small;
			big = temp;
		}
		printf("\nGCD of %d and %d is %d\n", data->data_1.nbr1,
			data->data_1.nbr2, small);
	}
}

void	assign_small_and_big(int *s, int *b, int d1, int d2)
{
	if (d1 > d2) {
		*s = d2;
		*b = d1;
	}
	else {
		*s = d1;
		*b = d2;
	}
}

/*
	Euclidean algorithm
	Ex:
		number1 = 252
		number2 = 102
		252 / 102 = 2 remainder 48
		102 /  48 = 2 remainder  6
		 48 /   6 = 8 remainder  0
	--> stops there we found the GCD of 252 and 102
	<technic>
	our new dividend is our old divider
	our new divider is  our old remainder
*/

// =======================================PART 1 ENDS===================================================
// =======================================PART 2 STARTS=================================================

void	part2(t_main *data)
{
	printf("\n\033[33;1mTODO: Read two numbers and display their sums as pdf's way.\033[0m\n");

	//maximum 4 digit in input numbers so that max 5 digit can display < 9999 + 1 = 10000 >
	printf("\nFirst Number: ");
	scanf("%d",&data->data_2.nbr1); // receiving input
	while (!(data->data_2.nbr1 <= 9999 && data->data_2.nbr1 >= 0)){ //input check
		printf("\033[31mInvalid input ! Numbers between 0-9999 are valid !! \033[0m\n");
		printf("First Number: ");
		scanf("%d",&data->data_2.nbr1); // receiving input
	}
	printf("Second Number: ");
	scanf("%d",&data->data_2.nbr2); // receiving input
	while (!(data->data_2.nbr2 <= 9999 && data->data_2.nbr2 >= 0)){ //input check
		printf("\033[31mInvalid input ! Numbers between 0-9999 are valid !! \033[0m\n");
		printf("Second Number: ");
		scanf("%d",&data->data_2.nbr2); // receiving input
	}
	printf("\nResult: \n\t");
	printf("%7d\n\t%7d\n\t+\n\t-------\n\t%7d\n", data->data_2.nbr1, data->data_2.nbr2, data->data_2.nbr1 + data->data_2.nbr2); // printing output as pdf's way
}

// =======================================PART 2 ENDS=================================================
// =======================================PART 3 STARTS===============================================
/*
	function to find next digit !
	Ex: 245 --> 5 then 4 lastly 2
*/
static int	get_index_digit(int nbr, int i) {
	int j = 0;
	while (j <= i - 1) {
		nbr /= 10;
		j++;
	}
	return (nbr % 10);
}

/*
	get number of digits EX: 5 for 12345
*/
static int	get_digit_nbr(int nbr) {
	int	res = 0;
	if (nbr == 0) // special condition for 'zero' because it not entries the while at its first attempt but I has a digit (1).
		return (1);
	while (nbr != 0){
		nbr /= 10;
		res += 1;
	}
	return (res);
}

/*
	! puts spaces and next number properly !
	I have known printf("%*d",<digit_number>,<normal_number>);
	Ex:
		printf("%*d",5,78); --> I used 0 instead of ' ' to show it clearly
		-- 00078
	But 0 needs special rule so that I used my way for every number not only to 0
*/

void	put_space_and_nbr(int loop, int nbr, int m) {
	int i = 0;
	while (i < 10 - loop - m) {
		printf(" ");
		i++;
	}
	if (nbr == 0) {
		i = 0;
		while (i < loop) {
			printf("0");
			i++;
		}
		printf("\n\t");
	}
	else
		printf("%d\n\t", nbr);
}

void	part3(t_main *data)
{
	int	digit_nbr;
	int	rotated_digit;
	int	putted_nbr_digit;
	int	i = 0;

	printf("\n\033[33;1mTODO: Read two numbers and display their multiples as pdf's way. \n\033[0m"); 
	//maximum 3 digit in input numbers so that max 6 digit can display <999 * 999 = 998001>
	printf("\nFirst Number: ");
	scanf("%d",&data->data_3.nbr1); // receiving input
	while (data->data_3.nbr1 < 0 || data->data_3.nbr1 > 999){ // input check
		printf("\033[31mInvalid input ! Numbers between 0-999 are valid !! \033[0m\n");
		printf("First Number: ");
		scanf("%d",&data->data_3.nbr1); // receiving input
	}
	printf("Second Number: ");
	scanf("%d",&data->data_3.nbr2 ); // receiving input
	while (data->data_3.nbr2 < 0 || data->data_3.nbr2 > 999){ // input check
		printf("\033[31mInvalid input ! Numbers between 0-999 are valid !! \033[0m\n");
		printf("Second Number: ");
		scanf("%d",&data->data_3.nbr2); // receiving input
	}
	printf("\nResult: \n\t");
	if (data->data_3.nbr2 <= 9){ // special contidion for << 0-9 (inclusive as pdf's notation)>>
		printf("%10d\n\t%10d\n\t*\n\t----------\n\t%10d\n",data->data_3.nbr1, data->data_3.nbr2, data->data_3.nbr1 * data->data_3.nbr2);
	}
	else {
		printf("%10d\n\t%10d\n\t*\n\t----------\n\t",data->data_3.nbr1, data->data_3.nbr2);
		digit_nbr = get_digit_nbr(data->data_3.nbr2); // getting the digit number for how many line that we need to use
		while (i < digit_nbr)
		{
			rotated_digit = get_index_digit(data->data_3.nbr2, i); // getting next digit 
			if (rotated_digit == 0) { // special condition for < 0 >
				putted_nbr_digit = get_digit_nbr(data->data_3.nbr1);
				put_space_and_nbr(putted_nbr_digit , 0, i);
			}
			else {
				putted_nbr_digit = get_digit_nbr(rotated_digit * data->data_3.nbr1); // getting number that we have to put to line
				put_space_and_nbr(putted_nbr_digit, rotated_digit * data->data_3.nbr1, i); // putting ' ' and number as a proper way
			}
			i++;
		}
		printf("+\n\t----------\n\t%10d\n", data->data_3.nbr1 * data->data_3.nbr2); // drawing line
	}
}
/*
zero is the key point in this part
Ex: 102 * 401

Result:	   102
		   401
	*
	----------
		   102
	      000 --> important
		 408
	+
	----------
	     40902

		 --> that is important because I find each part with the next digit * number1
			102 * 1 = 102
			102 * 0 = 0--> to make it 000 I add special rule with if at line <206>
							line <161> I fill with zeros at that calculation for ex: 000 instead of one '0'
			102 * 4 = 408
*/
// =======================================PART 3 ENDS===============================================
// =======================================PART 4 STARTS=============================================

/*
	I haven't used 'else' condition to catch whats are conditions easily.
*/

void	part4(t_main *data)
{
	printf("\n\033[33;1mTODO: Read a numbers then print an output as pdf's way. \n\033[0m");
	printf("\nEnter A number between 1 and 10(inclusive): ");
	scanf("%d", &data->data_4.nbr); // Taking input
	if (data->data_4.nbr >= 10 || data->data_4.nbr <= 0) // Input check
		printf("\033[31m\nInvalid input !\n\033[0m"); // Invalid numbers < 0 - 10 (inclusive) are valid > Error message 
	else if (data->data_4.nbr > 5) // Input check 
		printf("\nThe integer you entered is greater than 5\n"); // Numbers (5, 10] for message 
	else if (data->data_4.nbr <= 5) // Input check 
		printf("\nThe integer you entered is less than or equal to 5\n"); // Numbers < 0 - 5 > (inclusive) for message
	return ;
}
// =======================================PART 4 ENDS===============================================
