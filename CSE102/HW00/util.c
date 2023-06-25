#include "util.h"

void fraction_print(int numerator, int denominator) {
	printf("%d//%d", numerator, denominator);
} /* end fraction_print */

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3) {
	*n3 = n1*d2 + n2*d1;
	*d3 = d1*d2;
	fraction_simplify(n3, d3);
} /* end fraction_add */

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3) {
    // printf("fraction_sub - TODO: Remove this printf and add the subtraction code...\n");
	int	t_n1, t_n2, t_d;

	t_n1 = n1 * d2;
	t_n2 = n2 * d1;
	t_d = d1 * d2;

	*n3 = t_n1 - t_n2;
	*d3 = t_d;
	fraction_simplify(n3, d3);
} /* end fraction_sub */

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3) {
	// printf("fraction_mul - TODO: Remove this printf and add the subtraction code...\n");
	int	t_n, t_d;

	t_n = n1 * n2;
	t_d = d1 * d2;

	*n3 = t_n;
	*d3 = t_d;
	fraction_simplify(n3, d3);
} /* end fraction_mul */

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3)
{
	// printf("fraction_div - TODO: Remove this printf and add the subtraction code...\n");
	int	t_n, t_d;

	t_n = n1 * d2;
	t_d = d1 * n2;

	*n3 = t_n;
	*d3 = t_d;
	fraction_simplify(n3, d3);
} /* end fraction_div */

/*			Simplify the given fraction such that they are divided by their GCD
	firstly, I find lower abs then decrease it to find first number to make their remainder 0
	after that I check they may be both negative so that I multiply it with -1;
	then divide them
*/
void fraction_simplify(int * n, int * d)
{
	int	res = 1;
	int	small;
	if (abs(*n) >= abs(*d))
		small = *d;
	else
		small = *n;
	while (small >= 1){
		if (*d % small == 0 && *n % small == 0){
			res = small;
			break;
		}
		small--;
	}
	if (*d < 0 && *n < 0)
		res *= -1;
	*d = *d / res;
	*n = *n / res;
} /* end fraction_div */
