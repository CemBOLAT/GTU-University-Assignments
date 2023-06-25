#ifndef _UTIL_H_
# define _UTIL_H_
# include <stdio.h>
# include <stdlib.h>
struct s_input
{
	int	n1;
	int	n2;
	int	d1;
	int	d2;
};

struct s_output
{
	int r_n;
	int	r_d;
};

typedef	struct s_data
{
	struct s_input	inputs;
	struct s_output	outputs;
} t_data;


void fraction_print(int numerator, int denominator);

void fraction_add(int n1, int d1, int n2, int d2, int * n3, int * d3);

void fraction_sub(int n1, int d1, int n2, int d2, int * n3, int * d3);

void fraction_mul(int n1, int d1, int n2, int d2, int * n3, int * d3);

void fraction_div(int n1, int d1, int n2, int d2, int * n3, int * d3);

void fraction_simplify(int * n, int * d);

#endif /* _UTIL_H_ */
