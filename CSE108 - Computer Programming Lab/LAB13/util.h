#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define TXT "./input.txt"

struct Node
{
	double Value;
	struct Node *left_node;
	struct Node *right_node;
};

struct BST
{
	struct Node *root;
};

struct BST	*generateBST(const char *filename);
struct BST	*tree_init(struct BST *root, double value);
void		addNode(struct BST *bst, double value);
void		removeNode(struct BST *bst, double value);
void		print_menu();
void		printTree(struct BST *bst);
struct Node	*searchNode(struct BST *bst, double value);
int			countNodes(struct BST *bst);
int			count_nodes(struct Node *root);
struct Node	*removeNodeRecursive(struct Node *root, double value);
struct Node	*findMinNode(struct Node *node);
int			getMaxDepth(struct BST *bst);
int			get_max_depth(struct Node *root);
int			countLeafNodes(struct BST *bst);
void		free_tree(struct Node *root);

#endif
