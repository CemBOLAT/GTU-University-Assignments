#include "util.h"

void add_family_tree(void){
	int input = -1;
	data *family_tree = (data *)malloc(sizeof(data)); // allocate memory for the family tree
	family_tree->family_size = 0; // initialize the family size to 0
	family_tree->tree = NULL; // initialize the tree to NULL

	while (input != 3 && input != 2){
		print_add_menu();
		scanf("%d", &input);
		switch (input){
			case 1: add_node(family_tree); break; // add a node to the family tree
			case 2: save_family_tree(family_tree); printf(YELLOW"\nReturning to main menu...\n"RESET); break; // save the family tree to a file and return to the main menu
			case 3: printf(YELLOW"\nReturning to main menu...\n"RESET); break;
			default: printf(RED"\nInvalid Input !\n"RESET);
		}
	}
	free_tree(family_tree);
}

void add_node(data *root)
{
	char name[50], mother[50], father[50]; // name of the person, mother and father
	int age; // age of the person
	int i_mom, i_dad; // index of the mother and father in the family tree
	t_tree *new_node = (t_tree *)malloc(sizeof(t_tree)); // allocate memory for the new node

	new_node->mother = NULL; // initialize the mother of the new node to NULL
	new_node->father = NULL; // initialize the father of the new node to NULL

	printf("Enter the name of the person: ");
	scanf("%s", name);
	printf("Enter the age of the person: ");
	scanf("%d", &age);
	if (!(root->tree)) // if the family tree is empty no need to check for the mother and father
	{
		root->tree = (t_tree **)malloc(sizeof(t_tree *)); // allocate memory for the first node
		root->tree[0] = new_node; // assign the new node to the first node
		root->tree[0]->name = strdup(name); // duplicate the name of the person
		root->tree[0]->age = age;  // assign the age of the person
		root->tree[0]->mother = NULL; // initialize the mother of the first node to NULL
		root->tree[0]->father = NULL; // initialize the father of the first node to NULL
		root->family_size++; // increment the family size
		printf(GREEN"%s has been added to the family tree successfully !\n" RESET, name); // print success message
		return;
	}
	printf("Enter the name of the mother: "); // if the family tree is not empty ask for the mother and father
	scanf(" %s", mother);
	printf("Enter the name of the father: ");
	scanf(" %s", father);
	i_mom = find_node(root, mother); // find the index of the mother in the family tree if it exists otherwise return -1
	i_dad = find_node(root, father);
	root->tree = (t_tree **)realloc(root->tree, sizeof(t_tree *) * (root->family_size + 1)); // allocate memory for the new node with the new size
	root->tree[root->family_size] = new_node;  // assign the new node to the last node
	root->tree[root->family_size]->name = strdup(name);
	root->tree[root->family_size]->age = age;
	if (i_mom != -1) // if the mother exists assign it to the new node
		root->tree[root->family_size]->mother = root->tree[i_mom];
	if (i_dad != -1) // if the father exists assign it to the new node
		root->tree[root->family_size]->father = root->tree[i_dad];
	root->family_size++; // increment the family size
	printf(GREEN"%s has been added to the family tree successfully !\n" RESET, name); // print success message
	return;
}

void save_family_tree(data *root){
	FILE	*fp;
	char	file_name[50];
	int		i = 0;

	get_file_name(file_name, 0); // get the next file name to save the family tree

	printf(GREEN"Saving family tree to %s...\n" RESET, file_name);


	fp = fopen(file_name, "w+"); // open the file to write
	if (!fp){
		printf(RED"File not found ! \n" RESET);
		return ;
	}
	// file format example: Name:John,Age:20,Mother:Mary,Father:Jack
	while (i < root->family_size){ // write the family tree to the file
		fprintf(fp, "Name:%s,Age:%d,", root->tree[i]->name, root->tree[i]->age); // write the name and age of the person
		if (root->tree[i]->mother) // write the mother and father of the person if they exist otherwise write NULL
			fprintf(fp, "Mother:%s,", root->tree[i]->mother->name);
		else
			fprintf(fp, "Mother:NULL,");
		if (root->tree[i]->father)
			fprintf(fp, "Father:%s\n", root->tree[i]->father->name);
		else
			fprintf(fp, "Father:NULL\n");
		i++;
	}
	fclose(fp); 
	printf(GREEN"%s has been saved successfully...\n" RESET, file_name);
}
