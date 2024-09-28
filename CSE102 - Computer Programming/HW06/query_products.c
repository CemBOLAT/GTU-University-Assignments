#include "util.h"

int		print_other_features();
int		how_man_occurs(int arr[], int size, int nbr);
void	f_use_filter(char str[], int i, int p_top, int ans[]);
int		f_get_comma_nbr(char str[]);
void	filter_the_filtered_array(int ans[], int size, int f_nbr);
int		f_get_full_line_nbr(int ans[], int size);
int		f_get_feature_len(char str[], int i);
int		f_get_feature_location(char str[], int i);
int 	f_get_start_point(char str[], int i);
void	is_element_alone_in_array(int ans[], int size);
int		f_get_location(char	str[], int i, int p_top);

void	filter_product(int *p_top, int *p_feature){
	int		input;

	if (*p_feature != 4){
		while (1){
			printf_filter_menu(1); // printing the submen of filtering
			scanf("%d", &input);

			switch (input){
				case 1: filter_by_brand(3, *p_top); return;
				case 2: filter_by_type(1, *p_top); return;
				case 3: filter_by_price(4, *p_top); return;
				case 4: filter_by_others(*p_top); return;;
				case 5: filter_by_multiple(*p_top); return;;
				default: printf("Invalid Input.\n");
			}
		}
	}
	else {
		while (1){
			printf_filter_menu(2); // printing the submen of filtering
			scanf("%d", &input);

			switch (input){
				case 1: filter_by_brand(3, *p_top); return;
				case 2: filter_by_type(1, *p_top); return;
				case 3: filter_by_price(4, *p_top); return;
				case 4: filter_by_multiple(*p_top); return;;
				default: printf("Invalid Input.\n");
			}
		}
	}
}

void	list_all(int *p_top, int *p_feature){
	FILE	*file = fopen(PRODUCT, "r");
	char	letter;

	draw_line();
	printf("PRODUCTS :\n\n");
	while (fscanf(file, "%c", &letter) != -1) // print the products directly
		printf("%c", letter);
	fclose(file);
}

// filter by brand
void	filter_by_brand(int location, int ptop) {
	/*
		c: comma_counter
		i: index (line)
		k: features: index
		n: index (ans)
		ans: array of the index of the filtered product lines.
	*/
	FILE	*file = fopen(PRODUCT, "r");
	char	str[6], letter;
	int		i = 1, c = 0, k = 0, input_len;
	int		ans[ptop], n = 0;
	printf("Enter The Brand \n >> ");
	scanf("%s", str);
	input_len = f_strlen(str);
	draw_line();

	for (int q = 0; q < ptop; q++) ans[q] = 0;
	while (i <= ptop + 1){
		c = 0;
		k = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n')
		{
			if (letter == ',')
				c++;
			else if (c == location){
				while (letter == str[k]){
					if (letter == ',' || letter == '\n') break;
					k++;
					fscanf(file, "%c", &letter);
				}
				if (k == input_len){
					ans[n] = i - 1;
					n++;
				}
				while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	if (n != 0){
		fseek(file, 0, SEEK_SET);
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n'){
			printf("%c", letter);
		}
		printf("%c", letter);
		fclose(file);
		print_output(ans, 1);
	}
	else{
		printf("No filtered Brand\n");
		fclose(file);
	}
}

// filter by type
void	filter_by_type(int location, int ptop)
{
	FILE	*file = fopen(PRODUCT, "r");
	char	str[2], letter;
	int		i = 1, c = 0, k = 0;
	int		ans[ptop], n = 0, input_len = 1;
	printf("Enter The Type \n >> ");
	scanf("%s", str);
	draw_line();
	for (int q = 0; q < ptop; q++) ans[q] = 0;
	while (i <= ptop + 1){
		c = 0;
		k = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n')
		{
			if (letter == ',')
				c++;
			else if (c == location){
				while (letter == str[k]){
					if (letter == ',' || letter == '\n') break;
					k++;
					fscanf(file, "%c", &letter);
				}
				if (k == input_len){
					ans[n] = i - 1;
					n++;
				}
				while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	if (n != 0){
		fseek(file, 0, SEEK_SET);
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n'){
			printf("%c", letter);
		}
		printf("%c", letter);
		fclose(file);
		print_output(ans, 1);
	}
	else{
		printf("No filtered Type\n");
		fclose(file);
	}
}

// filter by price
void	filter_by_price(int location, int ptop)
{
	FILE	*file = fopen(PRODUCT, "r");
	char	letter;
	int		ans[ptop], n = 0;
	int		i = 1, j = 0, c = 0, k = 0;
	float	total_price = 0, min_price, max_price;
	draw_line();
	printf("Enter The Min price \n >> ");
	scanf("%f", &min_price);
	printf("Enter The Max price \n >> ");
	scanf("%f", &max_price);
	while (min_price >= max_price){
		draw_line();
		printf("Invalid Input!\n");
		printf("Enter The Min price \n >> ");
		scanf("%f", &min_price);

		printf("Enter The Max price \n >> ");
		scanf("%f", &max_price);
	}

	for (int q = 0; q < ptop; q++) ans[q] = 0;
	while (i <= ptop + 1){
		c = 0;
		k = 0;
		total_price = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n')
		{
			if (letter == ',')
				c++;
			else if (c == location){
				while (letter != '.' && letter != '\n'){
					total_price = (total_price * 10) + (letter - '0'); // convert string to float
					fscanf(file, "%c", &letter);
				}
				if (total_price >= min_price && total_price <= max_price){
					ans[n] = i - 1;
					n++;
				}
				if (letter != '\n')
					while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	if (n != 0){
		draw_line();
		fseek(file, 0, SEEK_SET);
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n'){
			printf("%c", letter);
		}
		printf("%c", letter);
		fclose(file);
		print_output(ans, 1);
	}
	else{
		printf("No filtered Product\n");
		fclose(file);
	}
}

// filter for user_defined_features
void	filter_by_others(int ptop)
{
	FILE	*file;
	char	str[6], letter;
	int		i = 1, c = 0, k = 0, input_len, feature, location;
	int		ans[ptop], n = 0, limit = 0;
	limit = print_other_features();
	scanf("%d", &feature);
	while (!(feature >= 1 && feature <= limit)){
		printf("Invalid Input !\n");
		printf("Select Feature Title:\n >> ");
		scanf("%d", &feature);
	}
	printf("Enter the feature property:\n >> ");
	scanf("%s", str);
	input_len = f_strlen(str);
	file = fopen(PRODUCT, "r");
	location = 4 + feature; // 4 is the number of default features in the product struct
	for (int q = 0; q < ptop; q++) ans[q] = 0;
	while (i <= ptop + 1){
		c = 0;
		k = 0;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n')
		{
			if (letter == ',')
				c++;
			else if (c == location){
				while (letter == str[k]){
					if (letter == ',' || letter == '\n') break;
					k++;
					fscanf(file, "%c", &letter);
				}
				if (k == input_len){
					ans[n] = i - 1;
					n++;
				}
				while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	if (n != 0){
		draw_line();
		fseek(file, 0, SEEK_SET);
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n'){
			printf("%c", letter);
		}
		printf("%c", letter);
		fclose(file);
		print_output(ans, 1);
	}
	else{
		printf("No filtered Product \n");
		fclose(file);
	}
}

// filter for multiple features
void	filter_by_multiple(int	p_top){
	char	str[50];
	int		comma_nbr, seached_feature_nbr, filtered_array_size;
	int		i = 0;

	printf("Enter the elements you want to filter seperate them with commas ex:\n\
<< Brand,Samsung,type,O >>\n >>> ");
	scanf("%s", str);
	comma_nbr = f_get_comma_nbr(str);
	seached_feature_nbr = (comma_nbr + 1) / 2;
	int ans[p_top * seached_feature_nbr];
	for (int q = 0; q <= p_top * seached_feature_nbr; q++) ans[q] = -1;
	while (i < seached_feature_nbr){
		f_use_filter(str, i, p_top, ans);
		i++;
	}
	filter_the_filtered_array(ans, p_top * seached_feature_nbr, seached_feature_nbr);
	if (f_get_full_line_nbr(ans, p_top * seached_feature_nbr) != 0){
		draw_line();
		printf("Filtered Products:\n");
		usleep(10);
		print_output(ans, 1);
	}
	else{
		printf("No filtered Product\n");
	}
}

// get the number of filtered elements
int		f_get_full_line_nbr(int ans[], int size){
	int	i = 0, count = 0;
	while (i < size){
		if (ans[i] != -1 && ans[i] != -2) count++;
		i++;
	}
	return (count);
}

// filter the filtered array in multiple features to get the final result
void		filter_the_filtered_array(int ans[], int size, int f_nbr){
	int	i = 0, j = 0;
	while (i < f_nbr){
		j = 0;
		while (j < size){
			if (ans[j] != -2 && ans[j] != -1 && how_man_occurs(ans, size, ans[j]) != f_nbr){
				ans[j] = -2;
			}
			j++;
		}
		i++;
	}
	is_element_alone_in_array(ans, size);
}


// check if the element is alone in the array otherwise make it -2 to decrease 1
void	is_element_alone_in_array(int ans[], int size){
	int	i = 0, j = 0;
	while (i < size){
		j = i + 1;
		if (ans[i] != -1 && ans[i] != -2){
			while (j < size){
				if (ans[j] == ans[i] && ans[j] != -1 && ans[j] != -2){
					ans[j] = -2;
				}
				j++;
		}
		}
		i++;
	}
}

// get the number of occurence of an element in an array
int	how_man_occurs(int arr[], int size, int nbr){
	int	i = 0, count = 0;
	while (i < size){
		if (arr[i] == nbr) count++;
		i++;
	}
	return (count);
}

// update the filtereed array for each feature
void	f_use_filter(char str[], int loop, int p_top, int ans[]){
	int		location, c, i = 0, k, n = 0, input_len, input_start_point;
	FILE	*file;
	char	letter;
	/*
		the input in multiple is: Brand,Samsung,type,O
		f_get_feature_len(); returns the length of the feature for each time
			for ex: 5 for Brand in first filting
					4 for Type in second filting
		f_get_location(); returns the location of the feature int text file each time
			for ex: 2 for Brand in first filting (because it's the second feature in the text file)
					0 for Type in second filting
		f_get_start_point(); returns the start point of the feature in the string each time
			for ex: 0 for Brand in first filting
					14 for Type in second filting
	*/
	input_len = f_get_feature_len(str, loop);
	location = f_get_location(str, loop, p_top);
	input_start_point = f_get_start_point(str, loop);
	file = fopen(PRODUCT, "r");
	while (i < p_top + 1){
		c = 0;
		k = input_start_point;
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n')
		{
			if (letter == ',')
				c++;
			else if (c == location){
				while (letter == str[k]){
					if (letter == ',' || letter == '\n') break;
					k++;
					fscanf(file, "%c", &letter);
				}
				if (k - input_start_point == input_len){
					ans[n + (loop * p_top)] = i;
					n++;
				}
				if (letter != '\n')
					while (fscanf(file, "%c", &letter) != -1 && letter != '\n');
				break ;
			}
		}
		i++;
	}
	fclose(file);
}

int 	f_get_start_point(char str[], int i){
	int		j = 0, lock = 0;
	while (str[lock] != '\0'){
		if (j == (i * 2) + 1) break;
		if (str[lock] == ',') j++;
		lock++;
	}
	return (lock);
}

int		f_get_feature_len(char str[], int i){
	int		j = 0, lock = 0;
	while (str[lock] != '\0'){
		if (j == (i * 2) + 1) break;
		if (str[lock] == ',') j++;
		lock++;
	}
	j = lock;
	while (str[j] != ',' && str[j] != '\0') j++;
	return (j - lock);
}

int	f_get_location(char	str[], int i, int p_top){
	FILE	*file = fopen(PRODUCT, "r");
	char	letter;
	int		location = 0, j = 0, lock = 0;

	if (i != 0){
		while (str[lock] != '\0'){
			if (j == i * 2) break;
			if (str[lock] == ',') j++;
			lock++;
		}
	}
	fscanf(file, "%c", &letter);
	while (letter != '\n'){
		j = lock;
		if (letter == ',') location++;
		if (str[j] == letter){
			while (str[j] == letter && letter != ','){
				j++;
				fscanf(file, "%c", &letter);
			}
			if ((letter == ',' && str[j] == ',') || (letter == '\n' && str[j] == ',')) {
				fclose(file);
				return (location);
			}
		}
		fscanf(file, "%c", &letter);
	}
	fclose(file);
	return (location);
}
int	f_get_comma_nbr(char str[]){
	int	i = 0, res = 0;
	while (str[i] != '\0'){
		if (str[i] == ','){
			res++;
		}
		i++;
	}
	return (res);
}

// print the added features to select one of them
int	print_other_features(){
	FILE	*file = fopen(PRODUCT, "r");
	char	letter;
	int		index = 1;
	int		feature_counter = 0;
	fscanf(file, "%c", &letter);
	while (letter != '\n'){
		if (letter == ',') feature_counter++;
		else if (feature_counter == 5){ // 4 is the number of features default (+ 1) is the lowest number of features
			printf("   %d-) ", index);
			while (letter != '\n'){
				if (letter != ',')
					printf("%c", letter);
				else if (letter == ','){
					index++;
					printf("\n   %d-) ", index);
				}
				fscanf(file, "%c", &letter);
			}
			break ;
		}
		fscanf(file, "%c", &letter);
	}
	printf("\nFeature:\n >> ");
	fclose(file);
	return (index);
}
