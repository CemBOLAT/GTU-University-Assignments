#include "util.h"

int		is_pID_different(int pID[], int new, int index);

int	assign_pID(int pID[], int stop){
	FILE	*file = fopen(STOCK, "r");
	int		index = 0, res = 0, cur_line = 0, feature_counter = 0;
	char	letter;
	while (fscanf(file, "%c", &letter) != -1 && letter != '\n');

	while (cur_line < stop){
		res = 0;
		feature_counter = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n'){
			if (letter == ',') feature_counter++;
			else if (feature_counter == 1) res = (res * 10) + (letter - '0');
			else if (feature_counter == 2){
				if (is_pID_different(pID,res, index) == 1){
					pID[index] = res;
					index++;
				}
				break;
			}
		}
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n');
		cur_line++;
	}
	fclose(file);
	return (index);
}

int	is_pID_different(int pID[], int new, int index){
	int	i = 0;
	while (i < index){
		if (pID[i] == new) return 0;
		i++;
	}
	return (1);
}

int	search_stock_nbr(int pID[], int stock_nbr, int array_size){
	for (int i = 0; i < array_size; i++){
		if (pID[i] == stock_nbr)
			return (i);
	}
	return (-1);
}

void	create_export_file(int array_size, int stop, int stocks[][stop], int pID[]) {
	FILE	*file = fopen(EXPORT, "w+");
	int		index = 0, min_stock, max_stock;
	float	medi_nbr;
	fprintf(file, "pID,minimum_stock,maximum_stock,median_number\n");
	while (index < array_size){
		fprintf(file, "%d,", pID[index]);
		min_stock = f_min_stock(stocks[index]);
		fprintf(file, "%d,", min_stock);
		max_stock = f_max_stock(stocks[index]);
		fprintf(file, "%d,", max_stock);
		medi_nbr = medi_stock(stocks[index]);
		fprintf(file, "%.1lf\n", medi_nbr);
		index++;
	}
	fclose(file);
}

// returns min stock of a given array
int	f_min_stock(int arr[]){
	int	min, i = 0;
	min = arr[i];

	while (arr[i] != -1){
		if (arr[i] < min && arr[i] != -1)
			min = arr[i];
		i++;
	}
	return (min);
}

// returns max stock of a given array
int	f_max_stock(int arr[]){
	int	max, i = 0;
	max = arr[i];

	while (arr[i] != -1){
		if (arr[i] > max && arr[i] != -1)
			max = arr[i];
		i++;
	}
	return (max);
}

// returns median stock of a given array
float	medi_stock(int arr[]){
	int	arr_size = 0;
	int	index = 0;
	int	temp;
	while (arr[arr_size] != -1) arr_size++;
	for (int i = 0; i < arr_size - 1; i++){
		for (int j = 0; j < arr_size - i - 1; j++)
		if (arr[j] > arr[j + 1]){
			temp = arr[j];
			arr[j] = arr[j + 1];
			arr[j + 1] = temp;
		}
	}
	if (arr_size % 2 == 1){
		return (arr[(arr_size) / 2]);
	}
	return ((arr[arr_size / 2] + arr[(arr_size / 2) - 1]) / 2);
}
