#include "util.h"

/*
	Firstly I named my files names as part1.c part2.c ...
	Util.c has some colorful prints and banner thing.

	Firstly I used struct to reduce declared variables and make code less complicated but teacher banned to use array.
	after that, I thought struct may reduce my points. So that I didn't use it.
	Due to that I am sorry about making the code complicated and reduce the intelligibility.
*/


int main(void)
{
	print_banner();
	part1();
	part2();
	part3();
	return (0);
}

//========================part1 starts================================
/*
	<<< Taken from wikipedia >>>
	As a general rule, leap years are years that are a multiple of 4:

	1980, 1984...
	However, there are two exceptions to this rule:

	1. Years that are multiples of 100 are leap years that are only divisible by 400 without a remainder:
	1600 is a leap year but 1700 is not.

	2. To make the calculation even more precise, years divisible by 4000 (although divisible by 400) are not considered leap years:
	400 is a leap year but 4000 or 8000 not.
*/

void part1(void)
{
	// I use double to check the year is integer or not
	double year;

	draw_line();
	shell_print("\nTODO: Write a C function that prompts the user to enter a year, then \
determine and print whether the year is a leap year or not.\n",
				't', 1, -1);
	draw_line();
	shell_print("Please enter a year : ", 'i', 1, -1);
	scanf("%lf", &year);				  // taking input
	while (year < 0 || year != (int)year) // checking input
	{
		/*
			year < 0 is our negative part
			year != (int)year checks has the year number float points or not.
		*/
		shell_print("Invalid INPUT ! << You cannot enter negative or decimal number as a year. >>\n", 'e', 1, -1);
		shell_print("Please enter a year : ", 'i', 1, -1);
		scanf("%lf", &year);
	}
	/*
		In c '0' is 'false' the others are 'true'.
		For ex:
			nbr1 = 67
			nbr2 = 43
			nbr1 % nbr2		-->  24  means 'true' to make it false
			!(nbr1 % nbr2)	-->  '0' means 'false'
	*/
	if (!((int)year % 4000)) // if else statements for a year is leap or not
		shell_print("is not a leap year", 'e', 1, (int)year);
	else if (!((int)year % 400))
		shell_print("is a leap year", 's', 1, (int)year);
	else if (!((int)year % 100))
		shell_print("is not a leap year", 'e', 1, (int)year);
	else if (!((int)year % 4))
		shell_print("is a leap year", 's', 1, (int)year);
	else
		shell_print("is not a leap year", 'e', 1, (int)year);
	draw_line();
}
//========================part1 ends================================
//========================part2 starts==============================
#include "util.h"

/*
	Write a C function that prompts the user to enter two numbers and an operator (+, -, *, /,!,^,%). \
	Before enter two numbers and operator, you need to enter format of output(result). \
	There are 2 outputs for the enhanced calculator: “S” and “I”.
*/

// checking the given input is a valid operation
static int f_check_operation(char c);
// calculate the result
static double f_operataion_implementation(char c, double n1, double n2);
// special function to calculate factorial << I used recursive >>
static double get_factorial(int n1);
// Error conditions like 6/0 , 0^0, and -1!
static int f_error_check(double n1, double n2, char o, char format);
// printing result on s format as pdf's way
void s_format(int m, int n, char operation, char format, double first_operand, double second_operand, double res);
// geting numbers digit number
/*	for ex:
		432 --> 3
		2134 --> 4
		1 --> 1
		32 --> 2
*/
static int f_get_digit_nbr(long long int res);
/* extanding result to integer
--> for ex: 3.534 is res and this function returns 3534 to find total digit number */
static long long int f_convert_result(double res);

/*
	I used
	<<	while (getchar() != '\n');	>>
	to clear buffer to get input clearly.
*/

void part2(void)
{
	double res;
	char format, operation;
	int m, n;
	double first_operand, second_operand;

	shell_print("\nTODO: Creating enhanched calculator as pdf's way !\n", 't', 2, -1);
	draw_line();
	while (getchar() != '\n')
		; // clearing buff
	shell_print("Enter the format of output (S or I) : ", 'i', 2, -1);
	format = getchar(); // getting input
	while (format != 'S' && format != 'I')
	{
		while (getchar() != '\n')
			; // clearing buff
		shell_print("Invalid Input ! << Format must be 'S' or 'I'  >>\n", 'e', 2, -1);
		shell_print("Enter the format of output (S or I) : ", 'i', 2, -1);
		format = getchar();
	}
	if (format == 'S')
	{
		while (getchar() != '\n')
			;
		shell_print("Enter m and n values : ", 'i', 2, -1);
		scanf("%d %d", &m, &n);
		while (m <= n || m <= 0 || n < 0)
		{
			while (getchar() != '\n')
				;
			shell_print("Invalid Input ! << 'n' must be or lower than 'm' and both of them cannot be negative >> \n", 'e', 2, -1);
			/*
				I warned in case of equality becase
				for ex: 7 / 8 = 0.875
					if our m and n are 4
					it should print like .0875e1 but its hard to see '.' at the start
					to increase intelligibility I warned user.
			*/
			shell_print("Enter m and n values : ", 'i', 2, -1);
			scanf("%d %d", &m, &n);
		}
	}
	while (getchar() != '\n')
		;
	shell_print("Enter the operation (+, -, *, /,!,^,%) : ", 'i', 2, -1);
	operation = getchar();
	while (f_check_operation(operation) == 0)
	{
		while (getchar() != '\n')
			;
		shell_print("Invalid Input ! << Valid operations are (+, -, *, /,!,^,%) >>\n", 'e', 2, -1);
		shell_print("Enter the operation(+,-,/,*,%%,!) : ", 'i', 2, -1);
		operation = getchar();
	}
	shell_print("Enter the first operand : ", 'i', 2, -1);
	scanf("%lf", &first_operand);
	if (operation != '!')
	{
		shell_print("Enter the second operand : ", 'i', 2, -1);
		scanf("%lf", &second_operand);
	}
	if (f_error_check(first_operand, second_operand, operation, format) == -1)
		return;
	res = f_operataion_implementation(operation, first_operand, second_operand);
	if (format == 'I')
		printf(">> %g %c %g = %d\n", first_operand, operation, second_operand, (int)res);
	else if (format == 'S')
		s_format(m, n, operation, format, first_operand, second_operand, res);
}

static int f_check_operation(char c)
{
	if (c == '+' || c == '-' || c == '*' ||
		c == '/' || c == '!' || c == '^' || c == '%')
		return (1);
	return (0);
}

static double f_operataion_implementation(char c, double n1, double n2)
{
	switch (c)
	{
	case '+':
		return (n1 + n2);
		break;
	case '-':
		return (n1 - n2);
		break;
	case '*':
		return (n1 * n2);
		break;
	case '/':
		return ((double)n1 / (double)n2);
		break;
	case '%':
		return (fmod(n1, n2));
		break;
	case '^':
		return (pow(n1, n2));
	case '!':
		return (get_factorial((int)n1));
		break;
	}
	return (0);
}

static double get_factorial(int n1)
{
	if (n1 == 0 || n1 == 1)
		return (n1);
	else
		return (n1 * get_factorial(n1 - 1));
}

static int f_error_check(double n1, double n2, char o, char format)
{
	if (format == 'I' && (n1 != (int)n1 || n2 != (int)n2))
		return (shell_print("ERROR ! << You cannot use decimal numbers on integer calculation part! >> \n", 'e', 3, -1), -1);
	else if ((o == '/' || o == '%') && n2 == 0)
		return (shell_print("ERROR ! << Your denominator cannot be zero >> \n", 'e', 3, -1), -1);
	else if (o == '!' && n1 < 0)
		return (shell_print("ERROR ! << You cannot calculate negative factorial >> \n", 'e', 3, -1), -1);
	else if (o == '^' && n1 < 0 && n2 < 0)
		return (shell_print("ERROR ! << You cannot calculate 0 ^ 0 >> \n", 'e', 3, -1), -1);
	else if (o == '!' && (n1 != (int)n1))
		return (shell_print("ERROR ! << You cannot calculate factorial of decimal numbers ! >> \n", 'e', 3, -1), -1);
	return (1);
}

/*
	due to not using sprintf, the program crush when result has multiple floating point digits.
	Because the system stores the double numbers in a diffferent way.
	for ex:
		result = 324.2345 but when I want to make some calculations it acts like 324.2345999999999999999...
		I dont know why and I only found a way which was using sprintf but it was also forbidden.

	The input are these
	Enter the format of output (S or I) : S
	Enter m and n values : 8 5
	Enter the operation (+, -, *, /,!,^,%) : %
	Enter the first operand : 32.56
	Enter the second operand : 2
	>> add (printf("%lli", extended_result): <<line 271>> to see problem.)

*/
void s_format(int m, int n, char operation, char format, double first_operand, double second_operand, double res)
{
	long long int extended_result = f_convert_result(res);
	int total_digit_nbr = f_get_digit_nbr(extended_result);
	int integer_part = (int)res;
	int integer_digit_nbr = f_get_digit_nbr((long long int)integer_part);
	int decimal_digit_nbr = total_digit_nbr - integer_digit_nbr;
	int decimal_part = ((double)res - (double)integer_part) * pow(10, total_digit_nbr - integer_digit_nbr);

	if (total_digit_nbr > m)
		printf("\033[31mERROR ! << You cannot print the result with %d digits ! << %g >>\033[0m", m, res);
	else if (operation == '!') // ! has special rule because this operation has no second operand !
	{
		printf(">> %g! = ", first_operand); // decimal part == '0' so that no need to check n and decimal_part conditions
		if (n == 0)
			printf("%0*d", m, (int)res);
		else if (m - n >= integer_digit_nbr)
			printf("%0*.*lf", m + 1, n, res);
		else if (m - n < integer_digit_nbr)
			printf("%0*.*lfe%d", m + 1, n, res * pow(10, decimal_digit_nbr - n), -(decimal_digit_nbr - n));
	}
	else
	{
		printf(">> %g %c %g = ", first_operand, operation, second_operand);

		if (n == 0 && decimal_digit_nbr != 0)
			printf("%0*de%d", m, (int)(res * (pow(10, decimal_digit_nbr))), decimal_digit_nbr * -1);
		else if (n == 0)
			printf("%0*d", m, (int)res);
		else if (n == decimal_digit_nbr && m - n == integer_digit_nbr && n != 0)
			printf("%*.*lf", m + 1, n, res);
		else if (m - n >= integer_digit_nbr && n >= decimal_digit_nbr && n != 0)
			printf("%0*.*lf", m + 1, n, res);
		else if (m - n < integer_digit_nbr && n >= decimal_digit_nbr && n != 0)
			printf("%0*.*lfe%d", m + 1, n, res * pow(10, decimal_digit_nbr - n), -(decimal_digit_nbr - n));
		else if (m - n >= integer_digit_nbr && n < decimal_digit_nbr && n != 0)
			printf("%0*.*lfe%d", m + 1, n, res * pow(10, decimal_digit_nbr - n), -(decimal_digit_nbr - n));
	}
	printf("\n");
}

static long long int f_convert_result(double res)
{
	double temp = res;

	while (temp != (long long int)temp)
		temp *= 10;
	return ((long long int)temp);
}

static int f_get_digit_nbr(long long int res)
{
	int i = 0;

	while (res != 0)
	{
		res /= 10,
			i++;
	}
	return (i);
}

/*
	7 condition on 'S' format
	1--> 	total digit is more than m // ERROR
		Ex	:
			Result is 234.45
			'm' is 3 and 'n' is 2
	2-->	integer part's digit number is lower than m - n
			and decimal part's digit number is lower than n
		Ex	:	Result is 123.56
			'm' is 8 and 'n' is 5 --> m - n = 3
			>>>	123.56000 filling with '0' properly
	3--> 	integer part's digit number is higher than m - n
			and decimal part's digit number is lower than n
		Ex	:	Result is 2345.56
			'm' is 6 and 'n' is 3
			>>>	234.556e1 dividing result with 10^(decimal_digit_number - n) and adding 'e' and decimal_digit_number - n
	4--> 	integer part's digit number is lower than m - n
			and decimal part's digit number is higher than n
		Ex	:	Result is 2345.56
			'm' is 6 and 'n' is 1
			>>>	23455.6e-1 multiplying result with 10^((m - n) - integer_digit_number) and adding 'e' and ((m - n) - integer_digit_number) * -1)
	5-->	when n is 0 program makes left aligning !
			so that I used printf("0*.*%d", m...) instead of printf("%0*.*lf", m + << critic 1 >>); properly.

*/
//========================part2 ends================================
//========================part3 starts================================
#include "util.h"

/*
	Write a C function that prompts the user to enter the grades for three exams (out of 100) \
	and two assignments (out of 100), and then uses a function to calculate and print the final grade (out of 100) \
	according to the following formula: Final Grade = (Exam1 + Exam2 + Exam3) / 3 * 0.6 + (Assignment1 + Assignment2) / 2 * 0.4
*/

static int f_is_valid_grade_exam(int exam_grade_1, int exam_grade_2, int exam_grade_3);
static int f_is_valid_grade_asgn(int asgn_grade_1, int asgn_grade_2);

void part3(void)
{
	int exam_grade_1, exam_grade_2, exam_grade_3;
	int asgn_grade_1, asgn_grade_2;
	double final_grade;

	shell_print("\nTODO: Write a C function that prompts the user to enter \
the grades of exams and assignments then calculate and print final grade !\n",
				't', 3, -1);
	draw_line();
	shell_print("Enter 3 exam grades of student : ", 'i', 3, -1);
	scanf("%d %d %d", &exam_grade_1, &exam_grade_2, &exam_grade_3);
	while (f_is_valid_grade_exam(exam_grade_1, exam_grade_2, exam_grade_3) == 0)
	{
		shell_print("Invalid INPUT ! << Grades must be between 0-100 <inclusive>. >> \n", 'e', 3, -1);
		shell_print("Enter 3 grades of student : ", 'i', 3, -1);
		scanf("%d %d %d", &exam_grade_1, &exam_grade_2, &exam_grade_3);
	}
	shell_print("Enter 2 assignment grades of student : ", 'i', 3, -1);
	scanf("%d %d", &asgn_grade_1, &asgn_grade_2);
	while (f_is_valid_grade_asgn(asgn_grade_1, asgn_grade_2) == 0)
	{
		shell_print("Invalid INPUT ! << Grades must be between 0-100 <inclusive>. >>\n", 'e', 3, -1);
		shell_print("Enter 2 assignment grades of student : ", 'i', 3, -1);
		scanf("%d %d", &asgn_grade_1, &asgn_grade_2);
	}
	final_grade = ((exam_grade_1 + exam_grade_2 + exam_grade_3) * 0.2) + ((asgn_grade_1 + asgn_grade_2) * 0.2);
	if (final_grade >= 60)
		shell_print("Final grade is:", 'p', 3, final_grade);
	else
		shell_print("Final grade is:", 'f', 3, final_grade);
}

static int f_is_valid_grade_exam(int exam_grade_1, int exam_grade_2, int exam_grade_3)
{
	if ((exam_grade_1 < 0 || exam_grade_1 > 100) ||
		(exam_grade_2 < 0 || exam_grade_2 > 100) ||
		(exam_grade_3 < 0 || exam_grade_3 > 100))
		return (0);
	return (1);
}

static int f_is_valid_grade_asgn(int asgn_grade_1, int asgn_grade_2)
{
	if ((asgn_grade_1 < 0 || asgn_grade_1 > 100) ||
		(asgn_grade_2 < 0 || asgn_grade_2 > 100))
		return (0);
	return (1);
}
//================part3 ends===============================================
//================util starts==============================================

void draw_line(void)
{
	printf("\033[36m\n****************************\033[0m\n");
}

void shell_print(char *str, char flag, int part, double nbr)
{
	if (part == 1 && nbr != -1)
	{
		if (flag == 'i')
			printf("\033[33m%d %s\033[0m", (int)nbr, str);
		else if (flag == 'e')
			printf("\033[31m%d %s\033[0m", (int)nbr, str);
		else if (flag == 't')
			printf("\033[35m%d %s\033[0m", (int)nbr, str);
		else if (flag == 's')
			printf("\033[32m%d %s\033[0m", (int)nbr, str);
	}
	else if (part == 3 && nbr != -1)
	{
		if (flag == 'p')
			printf("\033[32m%s %.1lf Passed !\n\033[0m", str, nbr);
		else if (flag == 'f')
			printf("\033[31m%s %.1lf Failed !\n\033[0m", str, nbr);
	}
	else
	{
		if (flag == 'i')
			printf("\033[33m%s\033[0m", str);
		else if (flag == 'e')
			printf("\033[31m%s\033[0m", str);
		else if (flag == 't')
			printf("\033[35m%s\033[0m", str);
		else if (flag == 's')
			printf("\033[32m%s\033[0m", str);
	}
}

void print_banner(void)
{
	printf("\n\033[32m \
	>=>    >=>                                                                    >=> \n \
	>=>    >=>                                                                    >=>                >=>       >=>>=> \n \
	>=>    >=>    >=>     >===>>=>>==>    >==>    >=>      >=>    >=>     >> >==> >=>  >=>         >=>  >=>   >>   >=> \n \
	>=====>>=>  >=>  >=>   >=>  >>  >=> >>   >=>   >=>  >  >=>  >=>  >=>   >=>    >=> >=>        >=>     >=>      >=> \n \
	>=>    >=> >=>    >=>  >=>  >>  >=> >>===>>=>  >=> >>  >=> >=>    >=>  >=>    >=>=>          >=>      >=>    >=> \n \
	>=>    >=>  >=>  >=>   >=>  >>  >=> >>         >=>>  >=>=>  >=>  >=>   >=>    >=> >=>         >=>    >=>   >=> \n \
	>=>    >=>    >=>     >==>  >>  >=>  >====>   >==>    >==>    >=>     >==>    >=>  >=>          >==>      >======> \n \
	\t\t\t\t\t CEMAL BOLAT 210104004010 \033[0m\n\n");
}
//================util ends==============================================
