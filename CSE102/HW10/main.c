#include "util.h"

int main()
{
	int		input = -1;
	Book *ll_book = NULL;
	Student *ll_student = NULL;

	ll_book = init_ll_book(); // Read book.txt and store the data in a linked list
	ll_student = init_ll_student(); // Read student.txt and store the data in a linked list
	print_banner(); // Print the banner
	while (input != 9){ // Loop until the user enters 9
		print_menu(); // Print the menu
		printf("Enter a number from 1 to 9: "); // Ask the user to enter a number
		scanf("%d", &input);
		switch (input)
		{
			case 1: student_borrowed_books(ll_student); break;
			case 2: ll_book = add_book(ll_book); break;
			case 3: ll_book = delete_book(ll_book); break;
			case 4: ll_book = update_book(ll_book); break;
			case 5: filterAndSortBooks(ll_book); break;
			case 6: ll_book = reverse_book_list(ll_book); break;
			case 7: search_books(ll_book); break;
			case 8: borrow_return_books(&ll_student, &ll_book); break;
			case 9: printf("\nExiting...\n"); break;
			default: printf("\nInvalid input\n"); break;
		}
		update_txt(ll_book, ll_student); // Update book.txt and student.txt
	}
	free_ll_book(ll_book); // Free the memory allocated for the linked list
	free_ll_student(ll_student); // Free the memory allocated for the linked list
	return (0);
}

void student_borrowed_books(Student *ll_student){
	char ID[100];
	Student *tmp = ll_student;
	int i = 0;
	printf("Enter the ID of the student: ");
	scanf(" %[^\n]s", ID);
	while (tmp != NULL){ // Loop until the end of the linked list
		if (strcmp(tmp->ID, ID) == 0){
			if (i == 0) printf(GREEN "\n%s borrowed the following books \n\n", tmp->name);
			printf("%s\n", tmp->borrowed_books); // Print the borrowed books
			i = 1;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		printf(RED "\nStudent not found\n");
	printf(WHITE);
}

Book *add_book(Book *ll_book)
{
	Book *new_book = (Book *)malloc(sizeof(Book));
	char isbn[20];
	char title[100];
	char author[100];
	int pub_year;
	int method;

	do {
		printf("Enter ISBN: ");
		scanf(" %[^\n]s", isbn);
		if (ll_book_isbn_check(ll_book, isbn) == 1)
			printf(RED"\nThe ISBN is already in book.txt\n\n"WHITE);
		else break;
	} while (1);
	printf("Enter Title: ");
	scanf(" %[^\n]s", title);
	printf("Enter Author: ");
	scanf(" %[^\n]s", author);
	printf("Enter Publication Year: ");
	scanf("%d", &pub_year);
	do
	{
		printf("Enter 0 to FIFO 1 TO LIFO : ");
		scanf("%d", &method);
		if (method != 0 && method != 1)
			printf("Invalid input\n");
	} while (method != 0 && method != 1);
	new_book->isbn = strdup(isbn);	   // Allocate memory and copy the value
	new_book->title = strdup(title);   // Allocate memory and copy the value
	new_book->author = strdup(author); // Allocate memory and copy the value
	new_book->pub_year = pub_year;
	new_book->reserved_status = 0;
	new_book->next = NULL;
	if (method == 0) // FIFO
		ll_book = ll_add_tail(ll_book, new_book);
	else if (method == 1) // LIFO
		ll_book = ll_add_head(ll_book, new_book);
	return (ll_book);
}

Book *delete_book(Book *ll_book)
{
	Book *tmp = ll_book;
	Book *prev = NULL;
	int is_found = 0;
	char isbn[20];
	printf("Enter the ISBN of the book you want to delete: ");
	scanf("%s", isbn);
	while (tmp != NULL)
	{
		if (strcmp(tmp->isbn, isbn) == 0)
		{
			is_found = 1; // The book is found
			if (prev == NULL) ll_book = tmp->next; // If the book is the head of the linked list
			else if (tmp->next == NULL) prev->next = NULL; // If the book is the tail of the linked list
			else if (prev != NULL && tmp->next != NULL) prev->next = tmp->next; // If the book is in the middle of the linked list
			free(tmp->isbn);
			free(tmp->title);
			free(tmp->author);
			free(tmp);
			break;
		}
		prev = tmp; // Save the previous node
		tmp = tmp->next; // Go to the next node iteratively
	}
	if (is_found == 0) printf("Book not found\n");
	return (ll_book);
}

Book *update_book(Book *ll_book)
{
	Book *tmp = ll_book;
	char isbn[20];
	int is_found = 0, feature;
	printf("Enter the ISBN of the book you want to update: ");
	scanf("%s", isbn);

	do
	{
		printf("Enter the feature you want to update \n >> 1. Title, 2. Author, 3. Publication Year << \n >> ");
		scanf("%d", &feature);
		if (feature < 1 || feature > 3)
			printf("Invalid input\n");
	} while (feature < 1 || feature > 3);

	switch (feature)
	{
	case 1:
		while (tmp != NULL) // Loop until the end of the linked list
		{
			if (strcmp(tmp->isbn, isbn) == 0) // If the book is found
			{
				is_found = 1;
				printf("Enter the new title: ");
				scanf(" %[^\n]s", tmp->title);
				break;
			}
			tmp = tmp->next;
		}
		break;
	case 2:
		while (tmp != NULL)
		{
			if (strcmp(tmp->isbn, isbn) == 0) // If the book is found
			{
				is_found = 1;
				printf("Enter the new author: ");
				scanf(" %[^\n]s", tmp->author);
				break;
			}
			tmp = tmp->next;
		}
		break;
	case 3:
		while (tmp != NULL)
		{
			if (strcmp(tmp->isbn, isbn) == 0) // If the book is found
			{
				is_found = 1;
				printf("Enter the new publication year: ");
				scanf("%d", &(tmp->pub_year));
				break;
			}
			tmp = tmp->next;
		}
		break;
	}
	if (is_found == 0) // If the book is not found
		printf("Book not found\n");
	return (ll_book);
}

void filterAndSortBooks(Book *ll_book)	// Filter and sort books
{
	Book *tmp_list = NULL;
	int filterChoice, sortChoice;
	char filter[20];
	int is_found = 0;
	do
	{
		printf("Enter the feature you want to filter \n >> 0. Author 1. Publication Year << \n >> ");
		scanf("%d", &filterChoice);
		if (filterChoice < 0 || filterChoice > 1)
			printf("Invalid input\n");
	} while (filterChoice < 0 || filterChoice > 1);
	printf("Enter the filter << case-sensitive >> : ");
	scanf(" %[^\n]s", filter);
	do
	{
		printf("Enter the feature you want to sort \n >> 0. Title 1. Author 2. Publication Year << \n >> ");
		scanf("%d", &sortChoice);
		if (sortChoice < 0 || sortChoice > 3)
			printf("Invalid input\n");
	} while (sortChoice < 0 || sortChoice > 3);
	tmp_list = filter_books(ll_book, filterChoice, filter, &is_found); // Filter books

	if (is_found == 0)
		printf("No books found\n");
	else
	{ // Sort books
		if (sortChoice == 0)
			tmp_list = ll_sort_books(tmp_list, 0);
		else if (sortChoice == 1)
			tmp_list = ll_sort_books(tmp_list, 1);
		else if (sortChoice == 2)
			tmp_list = ll_sort_books(tmp_list, 2);
		ll_print_book(tmp_list);
	}
	free_ll_book(tmp_list); // Free the linked list of filtered and sorted books
}

Book *reverse_book_list(Book *ll_book)
{
	Book *tmp = ll_book;
	Book *prev = NULL;
	Book *next = NULL;
	while (tmp != NULL)
	{ // Reverse the linked list iteratively
		next = tmp->next; // Save the next node
		tmp->next = prev; // Reverse the link
		prev = tmp; // Save the previous node
		tmp = next; // Go to the next node
	}
	ll_book = prev; // Update the head of the linked list
	ll_print_book(ll_book); // Print the reversed linked list
	return (ll_book); // Return the head of the reversed linked list
}

void search_books(Book *ll_book)
{
	int input = -1, is_found = 0;
	Book *tmp = ll_book;
	char str[100];
	while (input < 0 || input > 2) // Loop until the input is valid
	{
		printf("Search by 0. ISBN  1. Author  2. Title\n");
		printf("Enter a number from 0 to 2: ");
		scanf("%d", &input);
		if (input < 0 || input > 2)
			printf("\nInvalid input\n");
	}
	printf("Enter the search term: ");
	scanf(" %[^\n]s", str);
	switch (input)
	{
	case 0:
	{
		while (tmp != NULL)
		{
			if (strcmp(tmp->isbn, str) == 0) // If the book is found
			{
				ll_print_book_node(tmp); // Print the book
				is_found = 1;
			}
			tmp = tmp->next;
		}
		break;
	}
	case 1:
	{
		while (tmp != NULL)
		{
			if (strcmp(tmp->author, str) == 0)
			{
				ll_print_book_node(tmp);
				is_found = 1;
			}
			tmp = tmp->next;
		}
		break;
	}
	case 2:
	{
		while (tmp != NULL)
		{
			if (strcmp(tmp->title, str) == 0)
			{
				ll_print_book_node(tmp);
				is_found = 1;
			}
			tmp = tmp->next;
		}
		break;
	}
	}
	if (is_found == 0) // If the book is not found
		printf("\nNo books found\n");
}

void borrow_return_books(Student **ll_student, Book **ll_book)
{
	int	method;

	do {
		printf("0. Borrow  1. Return\n");
		printf("Enter a number from 0 to 1: ");
		scanf("%d", &method);
		if (method < 0 || method > 1)
			printf("\nInvalid input\n");
	} while (method < 0 || method > 1);
	if (method == 0) // If the user wants to borrow a book
		borrow_book(ll_student, ll_book);
	else // If the user wants to return a book
		return_book(ll_student, ll_book);
}

void borrow_book(Student **ll_student, Book **ll_book)
{

	char isbn[100];
	Book *tmp = *ll_book;
	int i = 0;

	printf("Enter the ISBN of the book you want to borrow: ");
	scanf(" %[^\n]s", isbn);
	while (tmp != NULL)
	{
		if (strcmp(tmp->isbn, isbn) == 0) // If the book is found
		{
			if (tmp->reserved_status == 0)  // If the book is not borrowed
			{
				tmp->reserved_status = 1; // Borrow the book
				*ll_student = ll_add_tail_student(*ll_student, tmp); // Add the book to the student's linked list
				printf("\nBook successfully borrowed\n");
				i = 1;
			}
			else
				printf("\nBook is already borrowed\n");
			return;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		printf("Book not found\n");
}

void return_book(Student **ll_student, Book **ll_book)
{
	char isbn[100];
	Book *tmp = *ll_book;
	int i = 0;
	printf("Enter the ISBN of the book you want to return : ");
	scanf(" %[^\n]s", isbn);
	while (tmp != NULL)
	{
		if (strcmp(tmp->isbn, isbn) == 0) // If the book is found
		{
			if (tmp->reserved_status == 1) // If the book is borrowed
			{
				tmp->reserved_status = 0;
				*ll_student = delete_student(*ll_student, tmp); // Delete the book from the student's linked list
				printf("\nBook successfully returned\n");
			}
			else
				printf("\nBook is already returned\n");
			return;
		}
		tmp = tmp->next;
	}
	if (i == 0)
		printf("Book not found\n");
}

void	print_menu(void)
{
	printf(CYAN);
	printf("\n");
	printf("1. Students Borrowed Books\n");
	printf("2. Add Book\n");
	printf("3. Delete Book\n");
	printf("4. Update Book\n");
	printf("5. Filter and Sort Books\n");
	printf("6. Reverse Book List\n");
	printf("7. Search Books\n");
	printf("8. Borrow and Return Books\n");
	printf("9. Exit\n\n");
	printf(WHITE);
}

void update_txt(Book *ll_book, Student *student)
{
	FILE *fp = fopen(BOOK_TXT, "w");
	Book *tmp = NULL;

	tmp = ll_book;
	fprintf(fp, "ISBN,Title,Author,Publication Year,Reserved Status\n");
	while (tmp != NULL)
	{
		fprintf(fp, "%s,%s,%s,%d,%d\n", tmp->isbn, tmp->title, tmp->author, tmp->pub_year, tmp->reserved_status);
		tmp = tmp->next;
	}
	fclose(fp);
	fp = fopen(STD_TXT, "w");
	Student *tmp2 = NULL;
	tmp2 = student;
	fprintf(fp, "Name,ID,Borrowed Book\n");
	while (tmp2 != NULL)
	{
		fprintf(fp, "%s,%s,%s\n", tmp2->name, tmp2->ID, tmp2->borrowed_books);
		tmp2 = tmp2->next;
	}
	fclose(fp);
}


void print_banner(void)
{
	printf(GREEN "  _    _                                         _          __     __  ___ \n");
	printf(" | |  | |                                       | |         \\ \\   /_ |/ _ \\ \n");
	printf(" | |__| | ___  _ __ ___   _____      _____  _ __| | __  _____\\ \\   | | | | | \n");
	printf(" |  __  |/ _ \\| '_ ` _ \\ / _ \\ \\ /\\ / / _ \\| '__| |/ / |______> >  | | | | |  \n");
	printf(" | |  | | (_) | | | | | |  __/\\ V  V / (_) | |  |   <        / /   | | |_| |   \n");
	printf(" |_|  |_|\\___/|_| |_| |_|\\___| \\_/\\_/ \\___/|_|  |_|\\_\\      /_/    |_|\\___/     \n" WHITE);
}
