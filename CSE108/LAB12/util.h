#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

# define VIP 4
# define OD 3
# define VETERAN 2
# define NORMAL 1
# define LINE_MAX 100

# define PIORITY_MAX 4

# define TXT "./customer.txt"

typedef struct t_list
{
	char			*name;
	int				age;
	char			*priority;
	int				priority_level;
	struct t_list	*prev;
	struct t_list	*next;
} Customer;

void		print_menu(void);
Customer	*ll_init(void);
Customer	*node_init(char *name, int age, char *priority, int priority_level);
Customer	*insertCustomer(Customer *head);
Customer	*removeCustomer(Customer *head);
void		assign_priority(char *priority_name, int *level);
void		update_txt(Customer *head);
Customer	*ll_insert(Customer *head, char *name, int age, char *priority, int level);
void		displayCustomers(Customer *head);
void		searchCustomer(Customer *head, char *name);
Customer	*changePriority(Customer *head);
void		takeInputAndSearchCustomer(Customer *head);
void		free_list(Customer *head);
#endif
