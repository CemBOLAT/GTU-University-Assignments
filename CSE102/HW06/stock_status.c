#include "util.h"
// check stock with given branch and pID name
void	specified_branch_pID_name(int *s_top)
{
	FILE	*file = fopen(STOCK, "r");
	char	str[15], pID[15], letter;
	int		i = 1, c = 0, k = 0, branch_len, location = 2, ans_i = 0, printed_input = 0;
	int		ans[*s_top], n = 0;
	printf("Enter The Branch \n >> ");
	scanf("%s", str);
	printf("Enter The pID \n >> ");
	scanf("%s", pID);
	draw_line();
	branch_len = f_strlen(str);
	for (int q = 0; q < *s_top; q++) ans[q] = 0;
	while (i <= *s_top + 1){
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
				if (k == branch_len){
					ans[n] = i - 1;
					n++;
					printed_input++;
				}
				while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	fclose(file);
	if (printed_input == 0) printf("No products in %s for %s pID", str, pID);
	else{
		printed_input = 0;
		while (ans_i <= n){
			if(get_the_pid(ans[ans_i], pID) == 1){
				if (printed_input == 0) printf("sID,pID,branch,current_stock\n");
				print_line(ans[ans_i], 2);
				printed_input++;
		}
		ans_i++;
		}
	}
	if (printed_input == 0) printf("No products in %s for %s pID", str, pID);
}

// check stock with given branch
void	specified_branch(int *s_top)
{
	FILE	*file = fopen(STOCK, "r");
	char	str[15], letter;
	int		i = 1, c = 0, k = 0, input_len, location = 2;
	int		ans[*s_top], n = 0;
	printf("Enter The Branch \n >> ");
	scanf("%s", str);
	draw_line();
	input_len = f_strlen(str);
	for (int q = 0; q < *s_top; q++) ans[q] = 0;
	while (i <= *s_top + 1){
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
				if (k == input_len && letter == ',' && str[k] == '\0'){
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
		print_output(ans, 2);
	}
	else {
		fclose(file);
		printf("No products in %s", str);
	}
}
// check stock with given branch name and prints out_of_stock products
void	out_of_stock(int *s_top){
	FILE	*file = fopen(STOCK, "r");
	char	str[15], letter;
	int		i = 1, c = 0, k = 0, input_len, location = 2, ans_i = 0, printed_input = 0;
	int		ans[*s_top], n = 0;

	printf("Enter The Branch \n >> ");
	scanf("%s", str);
	draw_line();
	input_len = f_strlen(str);

	for (int q = 0; q < *s_top; q++) ans[q] = 0;
	while (i <= *s_top + 1){
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
					printed_input++;
				}
				while (fscanf(file, "%c", &letter) != -1) if (letter == '\n') break;
				break ;
			}
		}
		i++;
	}
	fclose(file);
	if (printed_input == 0) printf("No out of stock products in %s", str);
	else{
		printed_input = 0;
		while (ans_i <= n){
			if(get_the_stock(ans[ans_i]) == 1){
				if (printed_input == 0) print_start_once(2);
				print_line(ans[ans_i], 2);
				printed_input++;
			}
		ans_i++;
	}
	}
	if (printed_input == 0) printf("No out of stock products in %s", str);
}

// get_the_stock of that line
int get_the_stock(int line){
	FILE	*file = fopen(STOCK, "r");
	char	letter;
	int		line_counter = 0, location = 3, location_counter = 0;
	while (fscanf(file, "%c", &letter) != -1)
	{
	    location_counter = 0;
		if (letter == '\n'){line_counter ++;}
		else if (line_counter == line){
			while (fscanf(file, "%c", &letter) != '\n'){
				if (letter == ',') location_counter++;
				else if (location_counter == location){
					if (letter == '0') return 1;
					else return 0;
				}
			}
		}
	}
	fclose(file);
	return (-1);
}

// get_the_pid of that line
int get_the_pid(int line, char pID[]){
	FILE	*file = fopen(STOCK, "r");
	char	letter;
	int		line_counter = 0, location = 1, location_counter = 0, line_pID = 0;
	while (fscanf(file, "%c", &letter) != -1)
	{
		line_pID = 0;
		location_counter = 0;
		if (letter == '\n'){line_counter ++;}
		else if (line_counter == line){
			while (fscanf(file, "%c", &letter) != '\n'){
				if (letter == ',') location_counter++;
				else if (location_counter == location){
					while (letter != ','){
						line_pID = (line_pID * 10) + (letter - '0');
						fscanf(file, "%c", &letter);
					}
					if (line_pID == atoi(pID)) return 1;
					else return 0;
				}
			}
		}
	}
	fclose(file);
	return (-1);
}
