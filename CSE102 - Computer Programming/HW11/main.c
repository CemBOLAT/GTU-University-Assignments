#include "util.h"

int main(){
	int input = -1;

	while (input != 4){
		print_menu();
		scanf("%d", &input);
		switch (input){
			case 1: add_family_tree(); break;
			case 2: remove_family_tree_file(); break;
			case 3: load_family_tree(); break;
			case 4: printf(YELLOW "\nTerminating...\n" RESET); break;
			default: printf(RED"\nInvalid Input !\n" RESET);
		}
	}
}

void load_family_tree(void)
{
	int input = -1, file_nbr;
	char file_name[50];
	FILE *fp;
	data *family_tree = NULL;

	printf(MAGENTA);
	printf("Listing Family Trees: \n");
	file_nbr = get_file_name(file_name, 1);
	printf(" >> ");
	printf(RESET);
	scanf("%d", &input);
	while (input < 0 || input > file_nbr)
	{
		printf(RED"Invalid Input !\n >> " RESET);
		scanf("%d", &input);
	}
	file_name[6] = input + '0';

	printf("%s has been selected\n", file_name);
	fp = fopen(file_name, "r");
	family_tree = load_family(fp);
	fclose(fp); // Close the file before returning from the function

	do {
		print_load_menu();
		scanf("%d", &input);
		switch (input)
		{
			case 1: add_node(family_tree); break;
			case 2: remove_node(family_tree); break;
			case 3: print_nuclear(family_tree); break;
			case 4: search_relative(family_tree); break;
			case 5: printf("\nReturning to the main menu...\n"); break;
			default: printf("\nInvalid Input!\n");
		}
	} while (input != 5);


	save_family_tree2(family_tree, file_name);

	free_tree(family_tree);
}
