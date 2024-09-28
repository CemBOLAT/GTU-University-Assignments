#include "util.h"

void search_relative(data *tree){
	int input = -1;
	char name[50];
	printf("Enter the name of the person: ");
	scanf(" %s", name);

	if (find_node(tree, name) == -1){ // if the person is not in the tree
		printf(RED"%s is not a family member !\n" RESET, name);
		return ;
	}

	do {
		print_search_menu();
		scanf("%d", &input);
		if (input < 1 || input > 5)
			printf(RED"Invalid Input !\n"RESET);
	} while (input < 1 || input > 5);

	switch (input){
		case 1: search_parent(tree, name); break;
		case 2: search_spouse(tree, name); break;
		case 3: search_children(tree, name); break;
		case 4: search_grandparents(tree, name); break;
		case 5: search_cousins(tree, name); break;
		default: printf(RED"Invalid Input !\n"); break;
	}
}

void search_parent(data *tree, char *name){
	int i = 0;
	if (!tree)
		return ;
	printf("Printing parents of %s\n", name); // print the parents of the person
	while (i < tree->family_size){
		if (strcmp(tree->tree[i]->name, name) == 0){
			if (tree->tree[i]->mother)
				printf("Mother: %s\n", tree->tree[i]->mother->name);
			else
				printf("Mother: None\n");
			if (tree->tree[i]->father)
				printf("Father: %s\n", tree->tree[i]->father->name);
			else
				printf("Father: None\n");
			return ;
		}
		i++;
	}
}

void search_spouse(data *tree, char *name)
{
	int i = 0;
	if (!tree)
		return ;
	printf("Printing spouse of %s\nSpouse: ", name); // print the spouse of the person
	while (i < tree->family_size){
		if (tree->tree[i]->mother && strcmp(tree->tree[i]->mother->name, name) == 0){
			if (tree->tree[i]->father)
				printf("%s", tree->tree[i]->father->name);
			else
				printf("None");
			printf("\n");
			return ;
		}
		else if (tree->tree[i]->father && strcmp(tree->tree[i]->father->name, name) == 0){
			if (tree->tree[i]->mother)
				printf("%s", tree->tree[i]->mother->name);
			else
				printf("None");
			printf("\n");
			return ;
		}
		i++;
	}
}

void search_children(data *tree, char *name){
	int i = 0;
	int flag = 0;
	if (!tree)
		return ;
	printf("Printing children of %s\nChildren: ", name); // print the children of the person
	while (i < tree->family_size){
		if (tree->tree[i]->mother && strcmp(tree->tree[i]->mother->name, name) == 0){
			printf("%s ", tree->tree[i]->name);
			flag = 1;
		}
		else if ( tree->tree[i]->father && strcmp(tree->tree[i]->father->name, name) == 0){
			printf("%s ", tree->tree[i]->name);
			flag = 1;
		}
		i++;
	}
	if (flag == 0)
		printf("None");
	printf("\n");
}

void search_grandparents(data *tree, char *name){
	int i = 0;
	if (!tree)
		return ;
	printf("Printing grandparents of %s\n", name); // print the grandparents of the person
	while (i < tree->family_size){
		if (strcmp(tree->tree[i]->name, name) == 0){
			if (tree->tree[i]->mother){
				if (tree->tree[i]->mother->mother)
					printf("Maternal Grandmother: %s\n", tree->tree[i]->mother->mother->name);
				else
					printf("Maternal Grandmother: None\n");
				if (tree->tree[i]->mother->father)
					printf("Maternal Grandfather: %s\n", tree->tree[i]->mother->father->name);
				else
					printf("Maternal Grandfather: None\n");
			}
			else
				printf("Maternal Grandmother: None\nMaternal Grandfather: None\n");
			if (tree->tree[i]->father){
				if (tree->tree[i]->father->mother)
					printf("Paternal Grandmother: %s\n", tree->tree[i]->father->mother->name);
				else
					printf("Paternal Grandmother: None\n");
				if (tree->tree[i]->father->father)
					printf("Paternal Grandfather: %s\n", tree->tree[i]->father->father->name);
				else
					printf("Paternal Grandfather: None\n");
			}
			else
				printf("Paternal Grandmother: None\nPaternal Grandfather: None\n");
			return;
		}
		i++;
	}
}
void search_cousins(data *tree, char *name)
{
	if (!tree)
		return;
	int i = find_node(tree, name);
	int how_many_flag = 0;
	int father = 0, mother = 0, grandpa = 0, m_grandpa = 0;
	int *arr = (int *)malloc(sizeof(int) * tree->family_size);
	int j = 0;
	while (j < tree->family_size)
	{
		arr[j] = 0;
		j++;
	}
	printf("Printing cousins of %s\n", name);
	if (tree->tree[i]->father)
		father = find_node(tree, tree->tree[i]->father->name);
	if (tree->tree[i]->mother)
		mother = find_node(tree, tree->tree[i]->mother->name);
	if (father == -1 && mother == -1) {
		printf("Cousins: None\n");
		return;
	}
	if (tree->tree[father]->father) {
		grandpa = find_node(tree, tree->tree[father]->father->name);
	}
	if (tree->tree[mother]->father) {
		m_grandpa = find_node(tree, tree->tree[mother]->father->name);
	}
	if (grandpa == -1 && m_grandpa == -1) {
		printf("Cousins: None\n");
		return;
	}

	int flag = is_child_of(tree, tree->tree[grandpa]->name, arr);
	printf("Cousins: ");
	if (flag != 0)
	{
		for (int i = 0; i < tree->family_size; i++){
			if (arr[i] != father && arr[i] != mother && arr[i] != grandpa && arr[i] != m_grandpa){
				int *arr2 = (int *)malloc(sizeof(int) * tree->family_size);
				int flag2 = is_child_of(tree, tree->tree[arr[i]]->name, arr);
				if (flag2 != 0){
					printf("%s ", tree->tree[arr[i]]->name);
					how_many_flag = 1;
				}
				free(arr2);
			}
		}
	}
	flag = is_child_of(tree, tree->tree[i]->mother->name, arr);
	if (flag != 0)
	{
		for (int i = 0; i < tree->family_size; i++){
			if (arr[i] != father && arr[i] != mother && arr[i] != grandpa && arr[i] != m_grandpa){
				int *arr2 = (int *)malloc(sizeof(int) * tree->family_size);
				int flag2 = is_child_of(tree, tree->tree[arr[i]]->name, arr);
				if (flag2 != 0){
					printf("%s ", tree->tree[arr[i]]->name);
					how_many_flag = 1;
				}
				free(arr2);
			}
		}
	}
	free(arr);
	if (how_many_flag == 0)
		printf("None");
	printf("\n");
}
