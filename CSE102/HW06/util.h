#ifndef UTIL_H
# define UTIL_H
// printf, fprintf, scanf, fscanf, fseek, fclose
# include <stdio.h>
// atoi
# include <stdlib.h>
// usleep
# include <unistd.h>

# define PRODUCT "./product.txt"
# define STOCK "./stocks.txt"
# define TEMP "./temp.txt"
# define EXPORT "./export.txt"

# define MAX_LINE_SIZE 100

//main.c
int	get_line(int i);

// file_operations
void	file_operation(int *p_top, int *s_top, int *p_feature, int *s_feature);
void	add_product(int *p_top, int *p_feature);
void	delete_product(int *p_top);
void	update_product(int *p_top, int *feature_nbr);
void	add_feature(int *p_top, int *p_feature);
void	add_new_stock(int *s_top, int *s_feature);
void	delete_stock(int *s_top, int *s_feature);
void	update_stock(int *s_top, int *s_feature);

// query_products
void	query_products(int *p_top,int *p_feature);
void	list_all(int *p_top, int *p_feature);
void	filter_product(int *p_top, int *p_feature);
void	filter_by_brand(int location, int ptop);
void	filter_by_type(int location, int ptop);
void	filter_by_price(int location, int ptop);
void	filter_by_others(int p_top);
void	filter_by_multiple(int	p_top);
void	print_output_multi(int	ans[], int size);

// stock_status
void	check_stock_status(int *s_top);
void	specified_branch_pID_name(int *s_top);
void	specified_branch(int *s_top);
void	out_of_stock(int *s_top);
int		get_the_stock(int line);
int		get_the_pid(int line, char pID[]);
void	print_start_once(int	flag);
// stock control
void	stock_control_by_brand(int *p_top, int *s_top);
void	get_pid_of_products(int	ans[], char	lines[][30], int ptop);
void	get_price_of_products(int	ans[], char	lines[][30], int ptop);
void	get_stock_of_products(char	lines[][30], int stop, int n);
void	print_filtered_output(char lines[][30], int n);
int		search_stock_nbr(int pID[], int stock_nbr, int array_size);
// export report
void	create_export_file(int array_size, int stop, int stocks[][stop], int pID[]);
void	export_report(int *s_top);
int		f_max_stock(int arr[]);
int		f_min_stock(int arr[]);
float	medi_stock(int arr[]);
//util.c
int		f_strlen(const char *s1);
void	print_line(int i, int flag);
void	print_output(int nbr[], int flag);
void	print_line(int i, int flag);
int		assign_pID(int pID[], int stop);
int		search_stock_nbr(int pID[], int stock_nbr, int array_size);
// menu_print
void	draw_line(void);
void	print_banner(void);
void	print_main_menu(void);
void	print_file_menu(void);
void	print_search_menu(void);
void	printf_filter_menu(int flag);
void	print_stock_status(void);

#endif
