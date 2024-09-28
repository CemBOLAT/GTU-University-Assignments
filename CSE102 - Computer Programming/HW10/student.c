#include "util.h"

Student *init_ll_student(void)
{
	Student *ll_student = NULL;
	Student *tmp = NULL;
	FILE *fp = fopen(STD_TXT, "r");
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return NULL; // Return NULL if file opening fails
	}
	char line[MAX_LINE_LENGTH];
	fgets(line, sizeof(line), fp); // Skip the first line
	while (fgets(line, sizeof(line), fp) != NULL) // Read the file line by line
	{
		Student *new_node = (Student *)malloc(sizeof(Student) * 1); // Create a new node for each data element
		if (new_node == NULL)
		{
			printf("Memory allocation failed!\n");
			exit(0); // Exit the loop if memory allocation fails
		}
		line[strlen(line) - 1] = '\0';
		char name[30];
		char id[10];
		char book[30];
		sscanf(line, "%[^,],%[^,],%[^,]", name, id, book); // Read the line and store the data in the variables
		new_node->borrowed_books = strdup(book);
		new_node->name = strdup(name);
		new_node->ID = strdup(id);
		new_node->next = NULL;
		if (ll_student == NULL) // If the linked list is empty, set the new node as the head
		{
			ll_student = new_node;
			tmp = new_node;
		}
		else // If the linked list is not empty, add the new node to tail
		{
			tmp->next = new_node;
			tmp = tmp->next;
		}
	}
	fclose(fp);
	return (ll_student);
}

Student *ll_add_tail_student(Student *ll_student, Book *new_book) // Add a new node to the tail of the linked list
{
	char name[100];
	char ID[20];
	printf("Enter name: ");
	scanf(" %[^\n]s", name);
	printf("Enter ID: ");
	scanf(" %[^\n]s", ID);
	Student *new_student = (Student *)malloc(sizeof(Student));
	new_student->name = strdup(name);
	new_student->ID = strdup(ID);
	new_student->borrowed_books = strdup(new_book->title);
	if (ll_student == NULL)
		ll_student = new_student;
	else
	{
		Student *tmp = ll_student;
		while (tmp->next != NULL) // iter to the last node
			tmp = tmp->next;
		tmp->next = new_student; // add the new node to the tail
		new_student->next = NULL;
	}
	return (ll_student);
}

void free_ll_student(Student *ll_student) // Free the linked list
{
	if (ll_student == NULL) return;
	Student *tmp = ll_student;
	Student *prev = NULL;
	while (tmp != NULL)
	{
		prev = tmp;
		free(tmp->name);
		free(tmp->ID);
		free(tmp->borrowed_books);
		tmp = tmp->next;
		free(prev);
	}
}

Student *delete_student(Student *ll_student, Book *new_book)
{
	Student *tmp = ll_student;
	Student *prev = NULL;
	int is_found = 0;

	while (tmp != NULL)
	{
		if (strcmp(tmp->borrowed_books, new_book->title) == 0)
		{
			if (prev == NULL) ll_student = tmp->next; // If the node to be deleted is the head
			else prev->next = tmp->next;

			free(tmp->name);
			free(tmp->ID);
			free(tmp->borrowed_books);
			free(tmp);

			is_found = 1;
			break;
		}

		prev = tmp;
		tmp = tmp->next;
	}

	if (is_found == 0)
	{
		printf("Book not found\n");
	}
	return ll_student;
}
