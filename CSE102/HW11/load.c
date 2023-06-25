#include "util.h"

data *load_family(FILE *fp)
{
	data *family_tree = (data *)malloc(sizeof(data));
	family_tree->family_size = 0;
	family_tree->tree = (t_tree **)malloc(sizeof(t_tree *) * 1);
	family_tree->tree[0] = NULL;

	char name[50], mother[50], father[50], line[150];
	int age, i_mom, i_dad;
	while (fgets(line, sizeof(line), fp))
	{
		t_tree *new_node = (t_tree *)malloc(sizeof(t_tree));
		new_node->mother = NULL;
		new_node->father = NULL;
		line[strlen(line) - 1] = '\0';
		sscanf(line, "Name:%[^,],Age:%d,Mother:%[^,],Father:%[^,]\n", name, &age, mother, father);
		if (strcmp(mother, "NULL") == 0)
		{
			new_node->mother = NULL;
		}
		else
		{
			i_mom = find_node(family_tree, mother);
			new_node->mother = family_tree->tree[i_mom];
		}
		if (strcmp(father, "NULL") == 0)
		{
			new_node->father = NULL;
		}
		else
		{
			i_dad = find_node(family_tree, father);
			new_node->father = family_tree->tree[i_dad];
		}
		new_node->name = strdup(name);
		new_node->age = age;
		family_tree->tree = (t_tree **)realloc(family_tree->tree, sizeof(t_tree *) * (family_tree->family_size + 1));
		family_tree->tree[family_tree->family_size] = new_node;
		family_tree->family_size++;
	}

	return family_tree;
}
