#ifndef UTIL_H
# define UTIL_H

#include "assets.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

typedef struct Node
{
	void			*data;
	struct	Node	*next;
} Node;

#ifndef BIN_FILE
# define BIN_FILE "./linkedlist.bin"
#endif

void	fillLinkedList(struct Node **head);
void	freeLinkedList(struct Node **head);
void	serializeLinkedList(struct Node* head);
void	print_data(void *data, int flag, int a);
void	f_exit(char *str);
void	f_draw_line();
void	deserializeLinkedList(struct Node **head);
void	free_file();

#endif
