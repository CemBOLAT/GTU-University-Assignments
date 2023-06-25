#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct s_order
{
	char	*customerName;
	int		orderID;
	char	*items;
	time_t	orderTime;
	struct	s_order *next;
} Order;

typedef struct
{
	Order	*top;
} LIFO;

typedef struct
{
	Order	*head;
	Order	*tail;
} FIFO;

# define FIFO_FILE "./fifo_data.bin"
# define LIFO_FILE "./lifo_data.bin"


void	serializeLIFO(LIFO *stack, const char *filename);
LIFO	*deserializeLIFO(const char *filename);
void	serializeFIFO(FIFO *queue, const char *filename);
FIFO	*deserializeFIFO(const char *filename);
void	displayFIFO(FIFO *queue);
void	displayLIFO(LIFO *stack);
void	displayOrder(Order *order);
void	enqueue(Order **list, char *customerName, int orderID, char *items, time_t orderTime);
Order	*dequeue(Order *list, time_t thresholdTime);
void	f_draw_line();
#endif
