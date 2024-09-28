#include "util.h"

void print_search_menu() {
	printf(CYAN);
	printf("*************************\n");
	printf("Select type of relatives:\n");
	printf("1-Parents\n");
	printf("2-Spouse\n");
	printf("3-Children\n");
	printf("4-Grandparents\n");
	printf("5-Cousins\n >> ");
	printf(RESET);
}

void print_menu(void) {
	printf(CYAN);
	printf("*************************\n");
	printf("1-Add Family Tree\n");
	printf("2-Remove Family Tree\n");
	printf("3-Load Family Tree\n");
	printf("4-Exit\n >> ");
	printf(RESET);
}

void print_add_menu(void) {
	printf(CYAN);
	printf("*************************\n");
	printf("1-Add Node\n");
	printf("2-Save Family Tree\n");
	printf("3-Exit\n >> ");
	printf(RESET);
}

void print_load_menu(void){
	printf(CYAN);
	printf("*************************\n");
	printf("Select an operation:\n");
	printf("1-Add new person\n");
	printf("2-Remove a person\n");
	printf("3-Print a Person's nuclear family\n");
	printf("4-Search Relatives of Given Person\n");
	printf("5-Return to the main menu\n >> ");
	printf(RESET);
}
