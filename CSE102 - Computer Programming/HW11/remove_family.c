#include "util.h"

void remove_family_tree_file(void){ // remove the family tree file
	FILE	*fp;
	char	str[50];
	printf("Enter the name of txt file of the family tree: ");
	scanf("%s", str);

	fp = fopen(str, "r");
	if (!fp){
		printf(RED"File not found ! \n" RESET);
		return ;
	}
	remove(str);
	printf(GREEN"%s has been removed successfully...\n" RESET, str);
	fclose(fp);
	printf(BLUE"Other files are shifting...\n" RESET);
	char file_name[50]; // shifting the files
	int i = str[6] - '0' + 1; // shifting the files
	strcpy(file_name, str);
	while (i < 10){
		file_name[6] = i + '0';
		FILE *fp = fopen(file_name, "r");
		char code[50];
		strcpy(code, "mv ");
		if (!fp)
			break;
		strcat(code, file_name);
		strcat(code, " ");
		file_name[6] = i - 1 + '0';
		strcat(code, file_name);
		strcat(code, "\n");
		system(code); // mv file_name file_name-1
		i++;
	}
	printf(GREEN"Shifting is done...\n"RESET);
}


void remove_node_recursive(data *tree, int index)
{
	// Base case: If the index is out of bounds, return
	if (index < 0 || index >= tree->family_size)
		return;

	// Recursively remove all children of the current node
	int i = 0;
	while (i < tree->family_size)
	{
		if (tree->tree[i]->mother == tree->tree[index] || tree->tree[i]->father == tree->tree[index]) {
			remove_node_recursive(tree, i);
		}
		else {
			i++; // Increment the index only when a child is not removed
		}
	}

	// Free memory for the name
	free(tree->tree[index]->name);

	// Shift elements in the tree array
	for (int i = index; i < tree->family_size - 1; i++) {
		tree->tree[i] = tree->tree[i + 1];
	}

	// Update family size and reallocate memory
	tree->family_size--;
	tree->tree = (t_tree **)realloc(tree->tree, sizeof(t_tree *) * tree->family_size);
}

void remove_node(data *tree)
{
	char name[50]; // Name of the person to remove
	int	child_index = -1; // Index of the child to remove
	printf("Enter the name of the person to remove: "); // Get the name from the user
	scanf(" %s", name);

	int index = find_node(tree, name);
	if (index == -1) {
		printf("Person not found.\n");
		return;
	}

	// Check if the person has children
	for (int i = 0; i < tree->family_size; i++) {
		if (tree->tree[i]->mother == tree->tree[index] || tree->tree[i]->father == tree->tree[index]) {
			child_index = i;
			break;
		}
	}
	if (child_index != -1) {
		char answer[50];
		printf(MAGENTA"Warning: %s has children, removing %s will also remove their children.\nDo you still want to continue (yes / no) : " RESET, name, name);
		scanf(" %s", answer);
		while (strcmp(answer, "yes") != 0 && strcmp(answer, "no") != 0) {
			printf(RED"Invalid answer, please enter yes or no: " RESET);
			scanf(" %s", answer);
		}
		if (strcmp(answer, "no") == 0){
			printf(YELLOW"Deletion aborted.\n" RESET);
			return;
		}
		else {
			printf(GREEN"%s and their children will be removed from the family tree.\n" RESET, name);
			remove_node_recursive(tree, index);
			return;
		}
	}

	remove_node_recursive(tree, index);
	printf(GREEN"%s has been removed from the family tree.\n"RESET, name);
}
