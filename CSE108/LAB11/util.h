#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_ll
{
	char		*cus_name;
	int			order_ID;
	char		*food;
	char		*order_time;
	struct s_ll	*next;
} Order;

typedef struct s_student
{
	char				*stu_name;
	long int			stu_number;
	int					score;
	struct s_student	*next;
} ExamPaper;

Order		*enqueue(Order *head, char *customerName, int orderID, char *items, char *orderTime);
Order		*dequeue(Order *queue);
void		display(Order *head);
void		updateOrder(Order *queue, int orderID, char *newItems);
ExamPaper	*pop(ExamPaper *stack);
ExamPaper	*push(ExamPaper *stack, char *studentName, long int studentNumber, int score);
int			isEmpty(ExamPaper *stack);
void		display_exam(ExamPaper *stack);
ExamPaper	*pop(ExamPaper *stack);
void		free_exam_paper(ExamPaper *stack);
void		free_order(Order *stack);
#endif
