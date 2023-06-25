#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define STD_TXT "student.txt"
#define BOOK_TXT "book.txt"
#define MAX_LINE_LENGTH 100

#define CYAN "\001\033[1;36m\002"
#define WHITE "\001\033[0m\002"
#define GREEN "\001\033[1;32m\002"
#define RED "\033[0;31m"

typedef struct s_book
{
	char	*isbn;
	char	*title;
	char	*author;
	int		pub_year;
	int 	reserved_status;
	struct s_book *next;
} Book;

typedef struct s_student
{
	char	*name;
	char	*ID;
	char	*borrowed_books;
	struct s_student *next;
} Student;

Book	*init_ll_book(void);
Student	*init_ll_student(void);
Book	*delete_book(Book *ll_book);
Book	*update_book(Book *ll_book);
Book	*ll_add_tail(Book *ll_book, Book *new_book);
Book	*ll_add_head(Book *ll_book, Book *new_book);
void	filterAndSortBooks(Book *ll_book);
void	ll_swap(Book *ll_index1, Book *ll_index2);
void	search_books(Book *ll_book);
void	ll_print_book(Book *ll_book);
void	ll_print_book_node(Book *ll_book);
void borrow_return_books(Student **ll_student, Book **ll_book);
Student *ll_add_tail_student(Student *ll_student, Book *new_book);
Student	*delete_student(Student *ll_student, Book *new_book);

void	print_menu(void);
Book	*add_book(Book *ll_book);
void	update_txt(Book *ll_book, Student *student);
void	free_ll_book(Book *ll_book);
void	free_ll_student(Student *ll_student);
Book	*reverse_book_list(Book *ll_book);
void borrow_book(Student **ll_student, Book **ll_book);
void	student_borrowed_books(Student *ll_student);
void return_book(Student **ll_student, Book **ll_book);
void borrow_book(Student **ll_student, Book **ll_book);
Book	*ll_sort_books(Book *ll_book, int choice);
Book	*filter_books(Book *ll_book, int filterChoice, char *filter, int *is_found);
void	print_banner(void);
int ll_book_isbn_check(Book *ll_book, char *isbn);

#endif
