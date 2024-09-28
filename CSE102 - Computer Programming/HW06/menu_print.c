#include "util.h"

void	print_main_menu()
{
	draw_line();
	printf("	Welcome operator, please select an option to continue:\n\
		1- File Operations\n\
		2- Query products\n\
		3- Check stock status\n\
		4- Stock control by brand\n\
		5- Export report\n >> ");
}

void	print_file_menu()
{
	draw_line();
    printf("	Select operation:\n");
    printf("		1-) Add a new product\n");
    printf("		2-) Delete a product\n");
    printf("		3-) Update a product\n");
    printf("		4-) Add feature to products\n");
    printf("		5-) Add a new stock entry\n");
    printf("		6-) Delete a stock entry\n");
    printf("		7-) Update a stock entry\n");
    printf("		8-) Back to main menu\n");
    printf(" >> ");
}

void	print_search_menu()
{
	draw_line();
    printf("	Select operation:\n");
    printf("		1-) List all products\n");
    printf("		2-) Filter products by brand, type, price, or a user-defined feature\n");
    printf("		3-) Back to main menu.\n");
    printf(" >> ");
}

void	printf_filter_menu(int flag)
{
	draw_line();
    if (flag == 1){
        printf("    Please select the type of filter:\n");
        printf("        1-) Brand\n");
        printf("        2-) Type\n");
        printf("        3-) Price\n");
        printf("        4-) Others\n");
        printf("        5-) Multiple Filter\n >> ");
    }
    else{
        printf("    Please select the type of filter:\n");
        printf("        1-) Brand\n");
        printf("        2-) Type\n");
        printf("        3-) Price\n");
        printf("        4-) Multiple Filter\n >> ");
    }
}

void    print_stock_status(void){
	draw_line();
    printf("    Please select the type of stock filter:\n");
    printf("        1-) All products in a specified branch by using the product ID and branch name\n");
    printf("        2-) All products in a specified branch\n");
    printf("        3-) Out-of-stock products in a specified branch\n");
    printf("        4-) Back to main menu.\n >> ");

}
