#include "util.h"


int main()
{
	struct BST	*root = generateBST(TXT);
	int			choice = 0;
	double		value;

	while (choice != 8){
		print_menu();
		scanf("%d", &choice);
		switch (choice){
		case 1:
			printf("Enter a value to add: ");
			scanf("%lf", &value);
			addNode(root, value);
			break;
		case 2:
			printf("Enter a value to delete: ");
			scanf("%lf", &value);
			removeNode(root, value);
			break;
		case 3:
			printf("Enter a value to search: ");
			scanf("%lf", &value);
			struct Node *node = searchNode(root, value);
			if (node != NULL) printf("Value found in %p\n", node);
			else printf("Value not found\n");
			break;
		case 4:
			int count_nodes = 0;
			count_nodes = countNodes(root);
			printf("Number of nodes: %d\n", count_nodes);
			break;
		case 5:
			int max_depth = 0;
			max_depth = getMaxDepth(root);
			printf("Maximum depth: %d\n", max_depth);
			break;
		case 6:
			int leaf_nodes = 0;
			leaf_nodes = countLeafNodes(root);
			printf("Number of leaf nodes: %d\n", leaf_nodes);
			break;
		case 7: printTree(root); break;
		case 8: printf("Exiting...\n"); break;
		default: printf("Invalid choice\n"); break;
		}
	}
	free_tree(root->root);
	free(root);
	return 0;
}

struct BST *generateBST(const char *filename)
{
	FILE *fp = fopen(filename, "r");
	double value;
	struct BST *root = NULL;

	if (fp == NULL)
	{
		printf("Error opening file\n");
		exit(1);
	}

	while (fscanf(fp, "%lf", &value) != -1) root = tree_init(root, value);

	fclose(fp); // Close the file after reading

	return root; // Return the generated BST
}

struct BST *tree_init(struct BST *root, double value)
{
	struct Node *new_node = NULL;
	struct Node *temp = NULL;

	if (root == NULL)
	{
		root = (struct BST *)malloc(sizeof(struct BST));
		if (root == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
		root->root = (struct Node *)malloc(sizeof(struct Node));
		if (root->root == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
		root->root->Value = value;
		root->root->left_node = NULL;
		root->root->right_node = NULL;
		return root;
	}
	else
	{
		new_node = (struct Node *)malloc(sizeof(struct Node));
		if (new_node == NULL)
		{
			printf("Memory allocation failed\n");
			exit(1);
		}
		new_node->Value = value;
		new_node->left_node = NULL;
		new_node->right_node = NULL;
		temp = root->root;
		while (temp != NULL)
		{
			if (value < temp->Value)
			{
				if (temp->left_node == NULL)
				{
					temp->left_node = new_node;
					return root;
				}
				else temp = temp->left_node;
			}
			else if (value > temp->Value)
			{
				if (temp->right_node == NULL)
				{
					temp->right_node = new_node;
					return root;
				}
				else temp = temp->right_node;
			}
		}
	}
	return root;
}

void addNode(struct BST *bst, double value){
	struct Node *new_node = NULL;
	struct Node *temp = NULL;

	new_node = (struct Node *)malloc(sizeof(struct Node));
	if (new_node == NULL){
		printf("Memory allocation failed\n");
		exit(1);
	}
	new_node->Value = value;
	new_node->left_node = NULL;
	new_node->right_node = NULL;
	temp = bst->root;
	while (temp != NULL){
		if (value == temp->Value)
		{
			printf("Value already exists\n");
			free(new_node); // Free the memory allocated for the new node
			return;
		}
		else if (value < temp->Value){
			if (temp->left_node == NULL){
				temp->left_node = new_node;
				return;
			}
			else temp = temp->left_node;
		}
		else if (value > temp->Value){
			if (temp->right_node == NULL){
				temp->right_node = new_node;
				return;
			}
			else temp = temp->right_node;
		}
	}
}

struct Node *removeNodeRecursive(struct Node *root, double value)
{
	if (root == NULL) return root;
	if (value < root->Value) root->left_node = removeNodeRecursive(root->left_node, value);
	else if (value > root->Value) root->right_node = removeNodeRecursive(root->right_node, value);
	else
	{
		if (root->left_node == NULL)
		{
			struct Node *temp = root->right_node;
			free(root);
			return temp;
		}
		else if (root->right_node == NULL)
		{
			struct Node *temp = root->left_node;
			free(root);
			return temp;
		}
		struct Node *temp = findMinNode(root->right_node);
		root->Value = temp->Value;
		root->right_node = removeNodeRecursive(root->right_node, temp->Value);
	}
	return root;
}

struct Node *findMinNode(struct Node *node)
{
	struct Node *tmp = node;
	while (tmp && tmp->left_node != NULL) tmp = tmp->left_node;
	return tmp;
}

void removeNode(struct BST *bst, double value)
{
	if (bst == NULL || bst->root == NULL)
	{
		printf("Error: BST is empty or not initilized.\n");
		return;
	}
	bst->root = removeNodeRecursive(bst->root, value);
}

struct Node *searchNode(struct BST *bst, double value){
	struct Node *temp = NULL;
	temp = bst->root;
	while (temp != NULL){
		if (value == temp->Value) return temp;
		else if (value < temp->Value) temp = temp->left_node;
		else if (value > temp->Value) temp = temp->right_node;
	}
	return NULL;
}

int countNodes(struct BST *bst) {
	int count =  count_nodes(bst->root);
}

int count_nodes(struct Node *root){
	if (root == NULL) return 0;
	return 1 + count_nodes(root->left_node) + count_nodes(root->right_node);
}

int getMaxDepth(struct BST* bst){
	int depth = 0;
	depth = get_max_depth(bst->root);
	return depth;
}

int get_max_depth(struct Node *root){
	if (root == NULL) return 0;
	int left_depth = get_max_depth(root->left_node);
	int right_depth = get_max_depth(root->right_node);

	if (left_depth > right_depth)
		return left_depth + 1;
	return right_depth + 1;
}

int	count_leaf_nodes(struct Node *root){
	if (root == NULL){
		return 0;
	}
	else if (root->left_node == NULL && root->right_node == NULL) return 1;

	return count_leaf_nodes(root->left_node) + count_leaf_nodes(root->right_node);
}

int countLeafNodes(struct BST* bst){
	int count = 0;
	count = count_leaf_nodes(bst->root);
	return count;
}

void print_tree(struct Node *root){
	if (root != NULL){
		print_tree(root->left_node);
		printf("%.2f\n", root->Value);
		print_tree(root->right_node);
	}
}

void  printTree(struct  BST*  bst){
	print_tree(bst->root);
}

void free_tree(struct Node *root){
	if (root != NULL){
		free_tree(root->left_node);
		free_tree(root->right_node);
		free(root);
	}
}

void print_menu(void){
	printf("1. Add a value\n");
	printf("2. Delete a value\n");
	printf("3. Search a value\n");
	printf("4. Count the number of nodes\n");
	printf("5. Count the number max depth\n");
	printf("6. Count the number of leaves\n");
	printf("7. Print the tree\n");
	printf("8. Exit\n >> ");
}
