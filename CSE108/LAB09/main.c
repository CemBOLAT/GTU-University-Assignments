#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define FILE_PATH "./furniture_database.txt"


typedef struct s_data
{

	char **name;
	char **color;
	double *price;
	int *serial_numbers;
	int *quantity;

} m_data;

int		f_get_size(m_data *data);
void	f_draw_line(void);
void	alocate_datas(m_data **data, int size_datas);
void	free_datas(m_data *data, int size_datas);
void	fill_datas(m_data *data, int size_datas);
void	print_menu();
void	see_all_furniture(m_data *data, int size_datas);
void	add_new_furniture(m_data *data, int *size_datas);
void	search_recursion(m_data *data, int size_datas, int input, char *str, int printed, int index);
void	search_furniture(m_data *data, int size_datas);
void	remove_furniture(m_data *data, int *size_datas);
void	print_item(m_data *data, int index);

void	program(m_data *data, int *size_datas){
	int	input = -1;

	while (input != 5){
		print_menu();
		scanf("%d", &input);
		f_draw_line();
		switch (input){
			case 1: see_all_furniture(data, *size_datas); break;
			case 2: add_new_furniture(data, size_datas); break;
			case 3: remove_furniture(data, size_datas); break;
			case 4: search_furniture(data, *size_datas); break;
			case 5: printf("Program terminated...\n"); break;
		}
	}
}

int main(void)
{
	m_data		*data;
	int			size_datas = f_get_size(data);
	alocate_datas(&data, size_datas);
	fill_datas(data, size_datas);
	program(data, &size_datas);
	free_datas(data, size_datas);

	return 0;
}

void	see_all_furniture(m_data *data, int size_datas){
	for (int i = 0; i < size_datas; i++){
		print_item(data, i);
	}
}

void add_new_furniture(m_data *data, int *size_datas) {
	FILE *file = fopen(FILE_PATH, "r+");
	char name[20], color[20];
	double price;
	int serial_number, quantity;
	printf("Please Enter the properties of the new furniture(Name, color, price, serial_number, quantity): ");
	scanf("%s %s %lf %d %d", name, color, &price, &serial_number, &quantity);
	while (!(quantity > 0 && serial_number > 0 && price > 0 && strcmp(name, "") != 0 && strcmp(color, "") != 0)) {
		printf("Please enter the properties correctly.\n");
		printf("Please Enter the properties of the new furniture(Name, color, price, serial_number, quantity): ");
		scanf("%s %s %lf %d %d", name, color, &price, &serial_number, &quantity);
	}
	fseek(file, 0, SEEK_END);
	(*size_datas)++;
	data->color = realloc(data->color, sizeof(char *) * (*size_datas));
	data->name = realloc(data->name, sizeof(char *) * (*size_datas));
	data->price = realloc(data->price, sizeof(double) * (*size_datas));
	data->serial_numbers = realloc(data->serial_numbers, sizeof(int) * (*size_datas));
	data->quantity = realloc(data->quantity, sizeof(int) * (*size_datas));
	fprintf(file, "%s %s %.2lf %d %d\n", name, color, price, serial_number, quantity);
	data->color[*size_datas - 1] = strdup(color);
	data->name[*size_datas - 1] = strdup(name);
	data->price[*size_datas - 1] = price;
	data->serial_numbers[*size_datas - 1] = serial_number;
	data->quantity[*size_datas - 1] = quantity;
	print_item(data, *size_datas - 1);
	fclose(file);
}


void	search_recursion(m_data *data, int size_datas, int input, char *str, int printed, int index){
	if (printed == 0 && index == size_datas) printf("No furniture found.\n");
	if (index < size_datas){
		if (input == 1){
			if (strcmp(data->name[index], str) == 0){
				print_item(data, index);
				printed = 1;
			}
		}
		else if (input == 2){
			if (strcmp(data->color[index], str) == 0){
				print_item(data, index);
				printed = 1;
			}
		}
		search_recursion(data, size_datas, input, str, printed, ++index);
	}
}

void	search_furniture(m_data *data, int size_datas){
	int		input;
	char	str[20];
	printf("Select a property to make search: \n");
	printf("\n1-Name\n");
	printf("2-Color\n\n >> ");
	scanf("%d", &input);
	while (input != 1 && input != 2){
		printf("Please enter a valid number: ");
		scanf("%d", &input);
	}
	if (input == 1) printf("Enter the name of product: ");
	else printf("Enter the color of product: ");
	scanf("%s", str);
	printf("\n");
	search_recursion(data, size_datas, input, str, 0, 0);
}

void	remove_furniture(m_data *data, int *size_datas){
	int index = -1;
	char name[20];
	printf("Enter the index of product you want to remove: ");
	scanf("%d", &index);
	FILE *file = fopen(FILE_PATH, "w+");
	while (index < 0 || index > *size_datas){
		printf("Please enter a valid index: ");
		scanf("%d", &index);
	}
	fprintf(file, "Name Color Price SerialNumber Quantity\n");
	for (int i = 0; i < *size_datas; i++){
		if (i != index) fprintf(file, "%s %s %.2lf %d %d\n", data->name[i], data->color[i], data->price[i], data->serial_numbers[i], data->quantity[i]);
		else{
			f_draw_line();
			printf("Following furniture is removed from the database: \n\n");
			print_item(data, i);
		}
	}
	free_datas(data, *size_datas);
	(*size_datas)--;
	alocate_datas(&data, *size_datas);
	fclose(file);
	fill_datas(data, *size_datas);
}


int f_get_size(m_data *data)
{
	FILE *file = fopen(FILE_PATH, "r");
	int size_datas = 0;
	char letter;
	while (fscanf(file, "%c", &letter) != -1)
	{
		if (letter == '\n') size_datas++;
	}
	fclose(file);
	return (size_datas - 1);
}

void alocate_datas(m_data **data, int size_datas)
{
	*data = (m_data *)malloc(sizeof(m_data));
	(*data)->name = (char **)malloc(sizeof(char *) * size_datas);
	(*data)->color = (char **)malloc(sizeof(char *) * size_datas);
	(*data)->price = (double *)malloc(sizeof(double) * size_datas);
	(*data)->serial_numbers = (int *)malloc(sizeof(int) * size_datas);
	(*data)->quantity = (int *)malloc(sizeof(int) * size_datas);
}

void free_datas(m_data *data, int size_datas)
{
	for (int i = 0; i < size_datas; i++)
	{
		free(data->name[i]);
		free(data->color[i]);
	}
	free(data->name);
	free(data->color);
	free(data->price);
	free(data->serial_numbers);
	free(data->quantity);
	free(data);
}

void fill_datas(m_data *data, int size_datas)
{
	FILE *file = fopen(FILE_PATH, "r");
	char name_temp[20];
	char color_temp[20];
	while (fgetc(file) != '\n');
	for (int i = 0; i < size_datas; i++)
	{
		fscanf(file, "%s %s %lf %d %d\n", name_temp, color_temp, &data->price[i], &data->serial_numbers[i], &data->quantity[i]);
		data->name[i] = strdup(name_temp);
		data->color[i] = strdup(color_temp);
	}
	fclose(file);
}

void	print_menu(){
	f_draw_line();
	printf("\033[32m1-See all furniture \n");
	printf("2-Add a new furniture\n");
	printf("3-Remove furniture\n");
	printf("4-Search furniture\n");
	printf("5-Exit\n");
	f_draw_line();
	printf("\033[0m");
	printf("Enter your choice: ");
}

void	print_item(m_data *data, int index){
	printf("Name: %s\n", data->name[index]);
	printf("Color: %s\n", data->color[index]);
	printf("Price: $%.2lf\n", data->price[index]);
	printf("Serial number: %d\n", data->serial_numbers[index]);
	printf("Quantity: %d\n", data->quantity[index]);
	printf("\n");

}

void f_draw_line()
{
    printf("\033[34m***************************************\n\033[0m");
}
