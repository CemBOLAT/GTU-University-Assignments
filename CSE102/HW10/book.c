#include "util.h"

Book *init_ll_book(void)
{
	Book *ll_book = NULL;
	Book *tmp = NULL;
	FILE *fp = fopen(BOOK_TXT, "r");
	char line[MAX_LINE_LENGTH];
	if (fp == NULL)
	{
		printf("Error opening file!\n");
		return NULL; // Return NULL if file opening fails
	}
	fgets(line, sizeof(line), fp); // Skip the first line
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		Book *new_node = (Book *)malloc(sizeof(Book)); // Create a new node for each data element
		if (new_node == NULL)
		{
			printf("Memory allocation failed!\n");
			exit(0); // Exit the loop if memory allocation fails
		}
		char isbn[20];
		char title[100];
		char author[100];
		int pub_year;
		int reserved_status;

		sscanf(line, "%[^,],%[^,],%[^,],%d,%d", isbn, title, author, &pub_year, &reserved_status);
		new_node->isbn = strdup(isbn);
		new_node->title = strdup(title);
		new_node->author = strdup(author);
		new_node->pub_year = pub_year;
		new_node->reserved_status = reserved_status;
		new_node->next = NULL;
		if (ll_book == NULL)
		{
			ll_book = new_node;
			tmp = new_node;
		}
		else
		{
			tmp->next = new_node;
			tmp = tmp->next;
		}
	}
	fclose(fp);
	return (ll_book);
}

Book *ll_add_head(Book *ll_book, Book *new_book)
{
	new_book->next = ll_book;
	ll_book = new_book;
	return (ll_book);
}

Book *ll_add_tail(Book *ll_book, Book *new_book)
{
	if (ll_book == NULL)
		ll_book = new_book;
	else
	{
		Book *tmp = ll_book;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_book;
		new_book->next = NULL;
	}
	return (ll_book);
}

void ll_print_book_node(Book *ll_book)
{
	printf("\n***************\n");
	printf("ISBN: %s\n", ll_book->isbn);
	printf("Title: %s\n", ll_book->title);
	printf("Author: %s\n", ll_book->author);
	printf("Publication Year: %d\n", ll_book->pub_year);
	printf("Reserved Status: %d\n", ll_book->reserved_status);
	printf("***************\n");
}

void ll_print_book(Book *ll_book)
{
	Book *tmp = ll_book;
	while (tmp != NULL)
	{
		ll_print_book_node(tmp);
		tmp = tmp->next;
	}
	return;
}

void ll_swap(Book *ll_index1, Book *ll_index2) // Swap the data of two nodes
{
	char *tmp_isbn = ll_index1->isbn;
	char *tmp_title = ll_index1->title;
	char *tmp_author = ll_index1->author;
	int tmp_pub_year = ll_index1->pub_year;
	int tmp_reserved_status = ll_index1->reserved_status;

	ll_index1->isbn = ll_index2->isbn;
	ll_index1->title = ll_index2->title;
	ll_index1->author = ll_index2->author;
	ll_index1->pub_year = ll_index2->pub_year;
	ll_index1->reserved_status = ll_index2->reserved_status;

	ll_index2->isbn = tmp_isbn;
	ll_index2->title = tmp_title;
	ll_index2->author = tmp_author;
	ll_index2->pub_year = tmp_pub_year;
	ll_index2->reserved_status = tmp_reserved_status;
}

void free_ll_book(Book *ll_book)
{
	if (ll_book == NULL)
		return;
	Book *tmp = ll_book;
	while (tmp != NULL)
	{
		free(tmp->isbn);
		free(tmp->title);
		free(tmp->author);
		Book *tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}

Book *filter_books(Book *ll_book, int filterChoice, char *filter, int *is_found)
{
	Book *tmp = ll_book;
	Book *return_list = NULL;
	while (tmp != NULL)
	{
		if (filterChoice == 0)
		{
			if (strcmp(tmp->author, filter) == 0)
			{
				*is_found = 1;
				Book *tmp_list = (Book *)malloc(sizeof(Book));
				tmp_list->isbn = strdup(tmp->isbn);
				tmp_list->title = strdup(tmp->title);
				tmp_list->author = strdup(tmp->author);
				tmp_list->pub_year = tmp->pub_year;
				tmp_list->reserved_status = tmp->reserved_status;
				tmp_list->next = NULL;
				return_list = ll_add_tail(return_list, tmp_list);
			}
		}
		else if (filterChoice == 1)
		{
			if (tmp->pub_year == atoi(filter))
			{
				*is_found = 1;
				Book *tmp_list = (Book *)malloc(sizeof(Book));
				tmp_list->isbn = strdup(tmp->isbn);
				tmp_list->title = strdup(tmp->title);
				tmp_list->author = strdup(tmp->author);
				tmp_list->pub_year = tmp->pub_year;
				tmp_list->reserved_status = tmp->reserved_status;
				tmp_list->next = NULL;
				return_list = ll_add_tail(return_list, tmp_list);
			}
		}
		tmp = tmp->next;
	}
	return (return_list);
}

Book *ll_sort_books(Book *ll_book, int choice)
{
	Book *ll_index1 = ll_book;
	Book *ll_index2 = NULL;

	switch (choice)
	{
	case 0:
	{
		while (ll_index1 != NULL)
		{
			ll_index2 = ll_index1->next;
			while (ll_index2 != NULL)
			{
				if (strcmp(ll_index1->title, ll_index2->title) > 0) ll_swap(ll_index1, ll_index2);
				ll_index2 = ll_index2->next;
			}
			ll_index1 = ll_index1->next;
		}
		break;
	}
	case 1:
	{
		while (ll_index1 != NULL)
		{
			ll_index2 = ll_index1->next;
			while (ll_index2 != NULL)
			{
				if (strcmp(ll_index1->author, ll_index2->author) > 0) ll_swap(ll_index1, ll_index2);
				ll_index2 = ll_index2->next;
			}
			ll_index1 = ll_index1->next;
		}
		break;
	}
	case 2:
	{
		while (ll_index1 != NULL)
		{
			ll_index2 = ll_index1->next;
			while (ll_index2 != NULL)
			{
				if (ll_index1->pub_year > ll_index2->pub_year) ll_swap(ll_index1, ll_index2);
				ll_index2 = ll_index2->next;
			}
			ll_index1 = ll_index1->next;
		}
		break;
	}
	}
	return ll_book;
}

int ll_book_isbn_check(Book *ll_book, char *isbn)
{
	Book *tmp = ll_book;
	while (tmp != NULL)
	{
		if (strcmp(tmp->isbn, isbn) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
