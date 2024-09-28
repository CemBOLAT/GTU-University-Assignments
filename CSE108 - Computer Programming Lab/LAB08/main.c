# include <stdio.h>
# include <math.h>

#define ARRAY_SIZE 3
#define COEF_ARRAY_SIZE 7

typedef struct s_matrix
{
	double	matrix[ARRAY_SIZE][ARRAY_SIZE];
} matrix;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
} vector;

typedef struct s_third_order_polynomial{
	double arr[4];
} third_order_polynomial;

typedef struct s_polynomial{
	double arr[COEF_ARRAY_SIZE];
} polynomial;

void		print_matrix(matrix initial_matrix);
int			inverse_matrix(matrix* initial_matrix, matrix* inverted_matrix);
double		determinant_of_matrix(matrix *initial_matrix);
double		find_orthogonal(vector vec_1, vector vec_2, vector* output_vec);
double		part2(vector vec_1, vector vec_2, vector* output_vec);
polynomial	get_integral(third_order_polynomial p1, third_order_polynomial p2, int a, int b);
void		f_draw_line(void);

int main(void)
{
	matrix					initial_matrix, inverted_matrix;
	vector					vec_1, vec_2, output_vec;
	third_order_polynomial	poly1, poly2;
	polynomial				integrated;
	int						a,b, error_code_of_part1;
	double					degree , upper = 0 , lower = 0;;

	for (int i = 0; i < ARRAY_SIZE; i++){
		for (int j = 0; j < ARRAY_SIZE; j++){
			printf("Enter the element [%d][%d] of the matrix: ", i, j);
			scanf("%lf", &initial_matrix.matrix[i][j]);
		}
		f_draw_line();
	}
	print_matrix(initial_matrix);
	f_draw_line();
	error_code_of_part1 = inverse_matrix(&initial_matrix, &inverted_matrix);
	if (error_code_of_part1 != -1)
		print_matrix(inverted_matrix);
	f_draw_line();
	degree = part2(vec_1, vec_2, &output_vec);
	printf("The Degree between the vectors is : %.2lf\n", degree);
	printf("The coordinates of the orthogonal vector: %.2f %.2f %.2f\n", output_vec.x, output_vec.y, output_vec.z);
	f_draw_line();
	printf("Please enter the coefs of first polynomial in order (4,5,1,2 for exp.): ");
	scanf("%lf %lf %lf %lf", &poly1.arr[0], &poly1.arr[1], &poly1.arr[2], &poly1.arr[3]);

	printf("Please enter the coefs of second polynomial in order (4,5,1,2 for exp.): ");
	scanf("%lf %lf %lf %lf", &poly2.arr[0], &poly2.arr[1], &poly2.arr[2], &poly2.arr[3]);

	printf("Please enter the interval that is used in integral (a, b): ");
	scanf("%d %d", &a, &b);

	integrated = get_integral(poly1, poly2, a, b);
	f_draw_line();
	for (int i = 0; i < 7 ; i++)
	{
		lower += integrated.arr[i]*pow(a, i + 1);
		upper += integrated.arr[i]*pow(b, i + 1);
	}
	double diff = upper - lower;
	printf("Integration of two polynomial: %.2lf\n", diff);
	return (0);
}

int inverse_matrix(matrix* initial_matrix, matrix *inverted_matrix){
	double determinant = determinant_of_matrix(initial_matrix);
	if (determinant == 0) {
		printf("Error: the matrix is not invertible.\n");
		return (-1);
	}
	double a = initial_matrix->matrix[0][0];
	double b = initial_matrix->matrix[0][1];
	double c = initial_matrix->matrix[0][2];
	double d = initial_matrix->matrix[1][0];
	double e = initial_matrix->matrix[1][1];
	double f = initial_matrix->matrix[1][2];
	double g = initial_matrix->matrix[2][0];
	double h = initial_matrix->matrix[2][1];
	double i = initial_matrix->matrix[2][2];
	double inv_determinant = 1.0 / determinant;
	inverted_matrix->matrix[0][0] = inv_determinant * (e * i - f * h);
	inverted_matrix->matrix[0][1] = inv_determinant * (c * h - b * i);
	inverted_matrix->matrix[0][2] = inv_determinant * (b * f - c * e);
	inverted_matrix->matrix[1][0] = inv_determinant * (f * g - d * i);
	inverted_matrix->matrix[1][1] = inv_determinant * (a * i - c * g);
	inverted_matrix->matrix[1][2] = inv_determinant * (c * d - a * f);
	inverted_matrix->matrix[2][0] = inv_determinant * (d * h - e * g);
	inverted_matrix->matrix[2][1] = inv_determinant * (b * g - a * h);
	inverted_matrix->matrix[2][2] = inv_determinant * (a * e - b * d);
	return (1);
}

void	print_matrix(matrix initial_matrix)
{
	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		for (int j = 0; j < ARRAY_SIZE; j++)
			printf("%.4f\t", initial_matrix.matrix[i][j]);
		printf("\n");
	}
	return ;
}

double determinant_of_matrix(matrix *initial_matrix){
	double a = initial_matrix->matrix[0][0];
	double b = initial_matrix->matrix[0][1];
	double c = initial_matrix->matrix[0][2];
	double d = initial_matrix->matrix[1][0];
	double e = initial_matrix->matrix[1][1];
	double f = initial_matrix->matrix[1][2];
	double g = initial_matrix->matrix[2][0];
	double h = initial_matrix->matrix[2][1];
	double i = initial_matrix->matrix[2][2];
	double det = a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
	return (det);
}

//==================================PART2==================================


double	part2(vector vec_1, vector vec_2, vector* output_vec)
{
	double	degree;
	printf("Enter the coordinates of the first vector: ");
	scanf("%lf %lf %lf", &vec_1.x, &vec_1.y, &vec_1.z);
	f_draw_line();
	printf("Enter the coordinates of the second vector: ");
	scanf("%lf %lf %lf", &vec_2.x, &vec_2.y, &vec_2.z);
	f_draw_line();
	degree = find_orthogonal(vec_1, vec_2, output_vec);
	return (degree);
}

double	find_orthogonal(vector vec_1, vector vec_2, vector* output_vec){
	double	skaler, abs_vec_1, abs_vec_2, cos_deg, degree;
	skaler = (vec_1.x * vec_2.x) + (vec_1.y * vec_2.y) + (vec_1.z * vec_2.z);
	abs_vec_1 = sqrt(pow(vec_1.x, 2) + pow(vec_1.y, 2) + pow(vec_1.z, 2));
	abs_vec_2 = sqrt(pow(vec_2.x, 2) + pow(vec_2.y, 2) + pow(vec_2.z, 2));
	cos_deg = skaler / (abs_vec_1 * abs_vec_2);
	degree = acos(cos_deg) * 180 / M_PI;
	output_vec->x = vec_1.y * vec_2.z - vec_1.z * vec_2.y;
	output_vec->y = vec_1.z * vec_2.x - vec_1.x * vec_2.z;
	output_vec->z = vec_1.x * vec_2.y - vec_1.y * vec_2.x;
	return (degree);
}

//==========================================================================

polynomial	get_integral(third_order_polynomial poly1, third_order_polynomial poly2, int a, int b){
	double		multiplied[COEF_ARRAY_SIZE];
	polynomial	integ_poly;
	polynomial	multi_poly;


	for (int i=0 ; i < COEF_ARRAY_SIZE ; i++)
	{
		multi_poly.arr[i] = 0;
		for (int j=0; j <= ARRAY_SIZE ; j++)
			if (i - j >= 0) multi_poly.arr[i] += poly1.arr[j] * poly2.arr[i - j];

	}
	for (int i = 0; i < COEF_ARRAY_SIZE; i++)
		integ_poly.arr[i] = multi_poly.arr[i] / (i + 1);
	return (integ_poly);
}

void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}
