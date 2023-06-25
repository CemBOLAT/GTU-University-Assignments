#include "util.h"

int	f_get_product_pID(char	lines[]);


// gets pid of products and add them to an array
void	get_pid_of_products(int	ans[], char	lines[][30], int ptop){
	FILE	*file = fopen(PRODUCT, "r");
	int		i = 0, k = 0, n = 0;
	char	letter;

	while (i <= ptop){
		k = 0;
		if (i == ans[n]){
			while (fscanf(file, "%c", &letter) && (letter != ',' && letter != '\n')){
				lines[n][k] = letter;
				k++;
			}
			lines[n][k] = letter;
			n++;
		}
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n');
		i++;
	}
	fclose(file);
}

// gets price of products and add them to an array
void	get_price_of_products(int	ans[], char	lines[][30], int ptop){
	FILE	*file = fopen(PRODUCT, "r");
	int		i = 0, k = 0, n = 0, f_counter = 0;
	char	letter, str_len;

	while (i <= ptop){
		f_counter = 0;
		if (i == ans[n]){
			while (fscanf(file, "%c", &letter) != -1 && letter != '\n' && f_counter <= 4){
				if (letter == ',')
					f_counter++;
				else if (f_counter == 4){
					k = f_strlen(lines[n]);
					lines[n][k] = letter;
				}
			}
			lines[n][k + 1] = ',';
			n++;
		}
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n');
		i++;
	}
	fclose(file);
}

// gets stock of products and add them to an array
void	get_stock_of_products(char	lines[][30], int stop, int arr_size){
	FILE	*file = fopen(STOCK, "r");
	int		i = 1, j = 0, k = 0, n = 0, stock_pID = 0, pID = 0, stock = 0, sum_stock = 0, product_pID = 0;
	char	letter, str_len, stock_pID_str[6];

	while (n < arr_size){
		char branch[10];
		fseek(file, 0, SEEK_SET);
		product_pID = f_get_product_pID(lines[n]); // get product pID
		j = 0;
		i = 0;
		k = 0;
		while(fscanf(file,"%c", &letter) != -1 && letter != '\n'); // iignore first line
		while (i <= stop){
			fscanf(file,"%d,%d,%[^,],%d\n",&stock_pID,&pID,branch,&stock);
			if (product_pID == pID){
				sum_stock += stock;
			}
			i++;
		}
		str_len = f_strlen(lines[n]);
		sprintf(stock_pID_str, "%d", sum_stock); // convert int to string
		while (stock_pID_str[j] != '\0'){ // add stock to lines
			lines[n][str_len + k] = stock_pID_str[j];
			j++;
			k++;
		}
		n++;
	}
	fclose(file);
}

// gets stock of products and returns them
int	f_get_product_pID(char	lines[]){
	int	res = 0, i = 0;
	while (lines[i] != ','){
		res = (res * 10) + lines[i] - '0';
		i++;
	}
	return (res);
}

// gets stock of products and returns them
void	print_filtered_output(char lines[][30], int n){
	int	len;

	printf("pID,price,current_stock\n");
	for (int i = 0; i < n; i++){
		len = f_strlen(lines[i]);
		printf("%s", lines[i]);
		if (lines[i][len - 1] == ',') printf("0\n");
		else printf("\n");
	}
}
