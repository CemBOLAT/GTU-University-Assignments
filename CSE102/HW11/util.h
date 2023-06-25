#ifndef UTIL_H
# define UTIL_H

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Colors
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

typedef struct s_node { // This is the node structure for the family tree's each member
	struct s_node	*mother;
	struct s_node	*father;
	int				age;
	char			*name;
} t_tree;

typedef struct s_data {
	t_tree			**tree; // This is the array of pointers to the nodes
	int				family_size;
} data;

// menu.c
void	print_menu(void);
void	print_add_menu(void);
void	print_load_menu(void);
void	print_search_menu();
//********************************************
// add_family_tree.c
void	add_family_tree(void);
void	save_family_tree(data *root);
void	add_node(data *root);
// *******************************************
// load.c
data	*load_family(FILE *fp);
//********************************************
// search.c
void	search_relative(data *tree);
void	search_parent(data *tree, char *name);
void	search_spouse(data *tree, char *name);
void	search_grandparents(data *tree, char *name);
void	search_children(data *tree, char *name);
void	search_cousins(data *tree, char *name);
//********************************************
// util.c
void	print_nuclear(data *tree);
int		find_node(data *root, char *name);
void	free_tree(data *root);
int		get_file_name(char file_name[], int flag);
void	f_print_siblings(data *tree, int i);
void	f_print_children(data *tree, int i);
void	save_family_tree2(data *root, const char *file_name);
int		is_child_of(data *tree, char *name, int *array);
//********************************************
// remove_family.c
void	remove_family_tree_file(void);
void	remove_node(data *tree);
void	remove_node_recursive(data *tree, int index);
//********************************************
// main.c
void	load_family_tree(void);
//********************************************

#endif
