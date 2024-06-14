#include <stdio.h>

typedef enum Operator {
	ADDITION,
	SUBTRACTION,
	MULTIPLICATION,
	DIVISION
} optype;

void	get_parameters(double *a, optype *op, double *b){
	char	opchar;

	printf("Type an arithmetic question (e.g. 1 + 2): ");
	scanf("%lf %c %lf", a, &opchar, b);

	switch(opchar){
		case '+':
			*op = ADDITION;
			break;
		case '-':
			*op = SUBTRACTION;
			break;
		case '*':
			*op = MULTIPLICATION;
			break;
		case '/':
			*op = DIVISION;
			break;
		default:
			printf("Invalid operator\n");
			break;
	}
}

void	print_result(double a, optype op, double b){
	switch(op){
		case ADDITION:
			printf("Result: %.2f\n", a + b);
			break;
		case SUBTRACTION:
			printf("Result: %.2f\n", a - b);
			break;
		case MULTIPLICATION:
			printf("Result: %.2f\n", a * b);
			break;
		case DIVISION:
			if(b == 0){
				printf("Division by zero\n");
			}else{
				printf("Result: %.2f\n", a / b);
			}
			break;
	}
}

int main(){
	double num1, num2;
	optype op;

	get_parameters(&num1, &op, &num2);
	print_result(num1, op, num2);
}
