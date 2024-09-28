#include "util.h"

void free_tree(data *root){ // free the family tree
	int i = 0;
	while (i < root->family_size){
		free(root->tree[i]->name); // free the name of the person in the node because it was duplicated using strdup
		free(root->tree[i]);
		i++;
	}
	free(root->tree);
	free(root);
}

int find_node(data *root, char *name) // find the index of the node in the family tree
{
	int i = 0;
	while (i < root->family_size)
	{
		if (strcmp(root->tree[i]->name, name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int get_file_name(char file_name[], int flag){ // get the next file name to save the family tree and print the existing files if flag is 1
	FILE *fp;
	int i = 1;
	file_name[0] = '\0';
	do {
		strcat(file_name, "family");
		file_name[6] = i + '0';
		file_name[7] = '\0';
		strcat(file_name, ".txt");
		fp = fopen(file_name, "r");
		if (fp && flag == 1){
			printf("%d-%s\n",i ,file_name);
		}
		if (fp){
			fclose(fp);
			i++;
		}
	} while (fp);
	return (i);
}

void f_print_siblings(data *tree, int i){ // print the siblings of the person in the node
	int j = 0;
	int flag = 0;
	printf("Siblings: ");
	while (j < tree->family_size){
		if (tree->tree[j]->mother && tree->tree[j]->father &&
			tree->tree[j]->mother == tree->tree[i]->mother &&
			tree->tree[j]->father == tree->tree[i]->father &&
			j != i) {
			if (flag == 0){
				flag = 1;
			}
			printf("%s ", tree->tree[j]->name);
		}
		j++;
	}
	if (flag == 1)
		printf("\n");
	else
		printf("None\n");
}

void f_print_children(data *tree, int i){ // print the children of the person in the node
	int j = 0;
	int flag = 0;
	printf("Children: ");

	while (j < tree->family_size){
		if (tree->tree[j]->mother == tree->tree[i] || tree->tree[j]->father == tree->tree[i]){
			if (flag == 0){
				flag = 1;
			}
			printf("%s ", tree->tree[j]->name);
		}
		j++;
	}
	if (flag == 1) printf("\n");
	else printf("None\n");
}

void print_nuclear(data *tree){ // print the nuclear family of the person
	char name[50];
	printf("Enter the name of the person: ");
	scanf(" %s", name);
	printf("Printing nuclear family of %s\n", name);
	int i = find_node(tree, name);
	if (i == -1){
		printf("Person not found\n");
		return ;
	}
	if (tree->tree[i]->father){
		printf("Father: %s\n", tree->tree[i]->father->name);
	}
	else
		printf("Father: None \n");
	if (tree->tree[i]->mother) {
		printf("Mother: %s\n", tree->tree[i]->mother->name);
	}
	else
		printf("Mother: None \n");
	f_print_siblings(tree, i);
	f_print_children(tree, i);
}

void save_family_tree2(data *root, const char *file_name) // save the family tree to extact file
{
	FILE *fp;
	int i = 0;

	fp = fopen(file_name, "w+");
	if (!fp)
	{
		printf("File not found!\n");
		return;
	}

	while (i < root->family_size)
	{
		fprintf(fp, "Name:%s,Age:%d,", root->tree[i]->name, root->tree[i]->age);
		if (root->tree[i]->mother)
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
	printf("%s has been saved successfully...\n", file_name);
}

int is_child_of(data *tree, char *name, int *array) // check if the person is a child of someone in the family tree
{
	int i;
	int j = 0;
	int is_child = 0;
	for (i = 0; i < tree->family_size; i++)
	{
		if (tree->tree[i]->father && strcmp(tree->tree[i]->father->name, name) == 0)
		{
			array[j] = i;
			j++;
			is_child++;
		}
		else if (tree->tree[i]->mother && strcmp(tree->tree[i]->mother->name, name) == 0)
		{
			array[j] = i;
			j++;
			is_child++;
		}
	}
	return (is_child);
}
