# include "util.h"

// it gets the number of needed information from texts files and returns it
int	get_line(int i);

int main(void)
{
	int	is_program_finished = 1, input;
	int	p_top, s_top, p_feature, s_feature;

	print_banner();
	/*
		p_top: number of products
		s_top: number of stock
		p_feature: number of product features
		s_feature: number of stock features
	*/
	p_top = get_line(0) - 1;
	s_top = get_line(1) - 1;
	p_feature = get_line(2);
	s_feature = get_line(3);
	while (is_program_finished == 1) {
		print_main_menu();
		scanf("%d", &input);
		switch (input){
			case 1: file_operation(&p_top, &s_top, &p_feature, &s_feature); break;
			case 2: query_products(&p_top, &p_feature); break;
			case 3: check_stock_status(&s_top); break;
			case 4: stock_control_by_brand(&p_top, &s_top); break;
			case 5: export_report(&s_top); is_program_finished = 0; break;
			default: printf("Invalid Input !\n"); break;
		}
	}
}

int	get_line(int flag)
{
	FILE	*file;
	char	letter;
	int		res = 0;

	if (flag == 0 || flag == 2)
		file = fopen(PRODUCT, "r+");
	else if (flag == 1 || flag == 3)
		file = fopen(STOCK, "r+");
	while (fscanf(file,"%c", &letter) != -1){
		if (letter == '\n' && (flag == 0 || flag == 1))
			res++;
		else if (letter == ',' && (flag == 2 || flag == 3))
			res++;
		else if (letter == '\n' && (flag == 2 || flag == 3))
			break;
	}
	fclose(file);
	return (res);
}

void	file_operation(int *p_top, int *s_top, int *p_feature, int *s_feature)
{
	int	is_program_finished = 1, input;

	while (is_program_finished == 1)
	{
		print_file_menu(); // sub menu
		scanf("%d", &input);
		switch (input){
			case 1: add_product(p_top, p_feature); break;
			case 2: delete_product(p_top); break;
			case 3: update_product(p_top, p_feature); break;
			case 4: add_feature(p_top, p_feature); break;
			case 5: add_new_stock(s_top, s_feature); break;
			case 6: delete_stock(s_top, s_feature); break;
			case 7: update_stock(s_top, s_feature); break;
			case 8: is_program_finished = 0; break;
			default: printf("Invalid Input !\n"); break;
		}
	}
}

// it lists the products with their features
void	query_products(int *p_top,int *p_feature)
{
	int	is_program_finished = 1, input;

	while (is_program_finished == 1)
	{
		print_search_menu();
		scanf("%d", &input);
		switch (input){
			case 1: list_all(p_top, p_feature); break;
			case 2: filter_product(p_top, p_feature); break;
			case 3: is_program_finished = 0; break;
			default: printf("Invalid Input !\n"); break;
		}
	}
}

// check stock status
void	check_stock_status(int *s_top){
	int	is_program_finished = 1, input;

	while (is_program_finished == 1)
	{
		print_stock_status();
		scanf("%d", &input);
		switch (input){
			case 1: specified_branch_pID_name(s_top); break;
			case 2: specified_branch(s_top); break;
			case 3: out_of_stock(s_top); break;
			case 4: is_program_finished = 0; break;
			default: printf("Invalid Input !\n"); break;
		}
	}
}
// stock control by brand (getting pID by brand and seach pID in stock.txt to get stock)
void	stock_control_by_brand(int *p_top, int *s_top)
{
	FILE	*file = fopen(PRODUCT, "r");
	char	brand[6], lines[(*s_top)][30], letter;
	int		brand_len, i = 1, c = 0, k = 0;
	int		ans[*p_top], n = 0;

	printf("Enter The Brand \n >> ");
	scanf("%s", brand);
	draw_line();
	brand_len = f_strlen(brand);;
	for (int q = 0; q < *p_top; q++) ans[q] = 0;
	for (int q = 0; q < *s_top; q++){
		for (int x = 0; x < 30; x++) lines[q][x] = '\0';
	}
	while (i <= (*p_top) + 1){
		c = 0;
		k = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n')
		{
			if (letter == ',')
				c++;
			else if (c == 3){
				while (letter == brand[k]){
					if (letter == ',' || letter == '\n') break;
					k++;
					fscanf(file, "%c", &letter);
				}
				if (k == brand_len && (letter == ',' || letter == '\n')){
					ans[n] = i - 1;
					n++;
				}
				while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	fclose(file);
	printf("\n");
	if (n != 0){
		get_pid_of_products(ans, lines, *p_top);
		usleep(10);
		get_price_of_products(ans, lines, *p_top);
		usleep(10);
		get_stock_of_products(lines, *s_top, n);
		print_filtered_output(lines, n);
	}
	else
		printf("Invalid Input !\n");
}

// lists pID's min_max and median of stocks to export.txt
void	export_report(int *s_top)
{
	FILE *file = fopen(STOCK, "r");
	int		pID[*s_top], stocks[*s_top][*s_top], array_size, pID_index, stock_nbr = 0, feature_counter = 0;
	int		inside_index, index = 0;
	char	letter;
	int		lined_pID;

	for(int i = 0; i < *s_top; i++) pID[i] = -1; // fill arrays with -1
	for(int i = 0; i < *s_top; i++) for (int j = 0; j < *s_top; j++) stocks[i][j] = -1;
	array_size = assign_pID(pID, *s_top);
	while (index < array_size){
		fseek(file, 0, SEEK_SET);
		usleep(10);
		stock_nbr = 0;
		feature_counter = 0;
		lined_pID = 0;
		inside_index = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n');
		while (fscanf(file, "%c", &letter) != -1){
			if (letter == '\n'){
				if (pID[index] == lined_pID){
				pID_index = search_stock_nbr(pID, lined_pID, array_size);
				if (pID_index != -1){
					while (stocks[pID_index][inside_index] != -1) inside_index++;
					stocks[pID_index][inside_index] = stock_nbr;
				}
				}
				stock_nbr = 0;
				feature_counter = 0;
				lined_pID = 0;
				inside_index = 0;
			}
			else if (letter == ',') feature_counter++;
			else if (feature_counter == 1){ // getting pIDs
				lined_pID = (lined_pID * 10) + letter - '0';
			}
			else if (feature_counter == 3){ // getting stock numbers
				stock_nbr = (stock_nbr * 10) + letter - '0';
			}
		}
		index++;
	}
	create_export_file(array_size, *s_top, stocks, pID);
	fclose(file);
}
