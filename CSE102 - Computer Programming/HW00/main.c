# include "util.h"

// I used struct to decrease variables to 1

int	main(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));

	//Homework 00 ascii art !
	printf("\033[32m _    _                                         _       ___   ___   \n");
	printf("|#|  |#|                                       | |     / _ \\ / _ \\  \n");
	printf("|#|__|#| ___  _ __ ___   _____      _____  _ __| | __ | | | | | | | \n");
	printf("|# __ #|/ _ \\| '_ ` _ \\ / _ \\ \\ /\\ / / _ \\| '__| |/ / | | | | | | | \n");
	printf("|#|  |#| (_) | | | | | |  __/\\ V  V / (_) | |  |   <  | |_| | |_| | \n");
	printf("|#|  |#|\\___/|_| |_| |_|\\___| \\_/\\_/ \\___/|_|  |_|\\_\\  \\___/ \\___/  \n\t\t\tCEMAL BOLAT 210104004010\n\n\033[0m");
	if (!data)
		return (0);
	printf("First Nominator : ");
	scanf("%d", &data->inputs.n1);
	printf("First Denominator : ");
	scanf("%d", &data->inputs.d1);
	printf("Second Nominator : ");
	scanf("%d", &data->inputs.n2);
	printf("Second Denominator : ");
	scanf("%d", &data->inputs.d2);

	if (data->inputs.d1 == 0 ||
		data->inputs.d2 == 0 ||
		data->inputs.n1 == 0)
	{
		printf("\033[31mINVALID PARAMETERS\n\033[0m");
		return (0);
	}
	printf("Addition :\t\t");
	fraction_add(data->inputs.n1, data->inputs.d1, \
						data->inputs.n2, data->inputs.d2, \
						&(data->outputs.r_n), &(data->outputs.r_d));
	fraction_print(data->inputs.n1, data->inputs.d1);
	printf(" + ");
	fraction_print(data->inputs.n2, data->inputs.d2);
	printf(" = ");
	fraction_print((data->outputs.r_n), (data->outputs.r_d));
	printf("\n");
	printf("Subtraction :\t\t");
	fraction_sub(data->inputs.n1, data->inputs.d1, \
						data->inputs.n2, data->inputs.d2, \
						&(data->outputs.r_n), &(data->outputs.r_d));
	fraction_print(data->inputs.n1, data->inputs.d1);
	printf(" - ");
	fraction_print(data->inputs.n2, data->inputs.d2);
	printf(" = ");
	fraction_print((data->outputs.r_n), (data->outputs.r_d));
	printf("\n");
	printf("Multiplication :\t");
	fraction_mul(data->inputs.n1, data->inputs.d1, \
						data->inputs.n2, data->inputs.d2, \
						&(data->outputs.r_n), &(data->outputs.r_d));
	fraction_print(data->inputs.n1, data->inputs.d1);
	printf(" * ");
	fraction_print(data->inputs.n2, data->inputs.d2);
	printf(" = ");
	fraction_print((data->outputs.r_n), (data->outputs.r_d));
	printf("\n");
	printf("Division :\t\t");
	fraction_div(data->inputs.n1, data->inputs.d1, \
						data->inputs.n2, data->inputs.d2, \
						&(data->outputs.r_n), &(data->outputs.r_d));
	fraction_print(data->inputs.n1, data->inputs.d1);
	printf(" / ");
	fraction_print(data->inputs.n2, data->inputs.d2);
	printf(" = ");
	fraction_print((data->outputs.r_n), (data->outputs.r_d));
	printf("\n");

	return (0);
}
