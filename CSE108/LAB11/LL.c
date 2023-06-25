#include "util.h"

Order *enqueue(Order *head, char *customerName, int orderID, char *items, char *orderTime)
{
	if (head == NULL)
	{
		head = (Order *)malloc(sizeof(Order));
		head->cus_name = strdup(customerName);
		head->order_ID = orderID;
		head->food = strdup(items);
		head->order_time = strdup(orderTime);
		head->next = NULL;
	}
	else
	{
		Order *newNode = (Order *)malloc(sizeof(Order));
		newNode->cus_name = strdup(customerName);
		newNode->order_ID = orderID;
		newNode->food = strdup(items);
		newNode->order_time = strdup(orderTime);
		newNode->next = head;
		head = newNode;
	}
	printf("Enqueued : Order ID %d, Customer Name : %s, Items : %s\n", orderID, customerName, items);
	return head;
}

Order *dequeue(Order * queue){
	Order *tmp = queue;
	Order *prev = NULL;
	if (tmp == NULL)
	{
		printf("Queue is empty\n");
		return queue;
	}
	while (tmp->next != NULL)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == NULL) queue = NULL;
	else prev->next = NULL;
	printf("Dequeued : Order ID %d, Customer Name : %s, Items : %s\n", tmp->order_ID, tmp->cus_name, tmp->food);
	free(tmp->cus_name);
	free(tmp->food);
	free(tmp->order_time);
	free(tmp);
	return queue;
}

void display(Order *head)
{
	if (head == NULL)
	{
		printf("Queue is empty\n");
		return;
	}
	printf("\nDisplay Orders by Order Time:\n\n");
	while (head != NULL)
	{
		printf("Customer Name : %s ,", head->cus_name);
		printf("Order Id : %d ,", head->order_ID);
		printf("Items : %s \n", head->food);
		head = head->next;
	}
	printf("\n");
}

void updateOrder(Order * queue, int orderID, char * newItems)
{
	Order *tmp = queue;
	int		isFound = 0;
	while (tmp != NULL)
	{
		if (tmp->order_ID == orderID)
		{
			printf("Updated Order: Order ID %d Customer Name: %s Items: %s\n", tmp->order_ID, tmp->cus_name, newItems);
			free(tmp->food);
			tmp->food = strdup(newItems);
			isFound = 1;
		}
		tmp = tmp->next;
	}
	if (isFound == 0) printf("Order ID not found\n");
}

ExamPaper *push(ExamPaper *  stack, char * studentName, long int studentNumber, int score){
	ExamPaper *newNode = (ExamPaper *)malloc(sizeof(ExamPaper));
	newNode->stu_name = strdup(studentName);
	newNode->stu_number = studentNumber;
	newNode->score = score;
	newNode->next = stack;
	printf("Exam Paper Added: Student Name: %s, Student Number: %ld, Score: %d\n", studentName, studentNumber, score);
	return newNode;
}

ExamPaper * pop(ExamPaper * stack)
{
	if (stack == NULL)
	{
		printf("Stack is empty\n");
		return stack;
	}
	ExamPaper *tmp = stack;
	stack = stack->next;
	printf("Last Added Exam Paper: Student Name: %s, Student Number: %ld, Score: %d\n", tmp->stu_name, tmp->stu_number, tmp->score);
	free(tmp->stu_name);
	free(tmp);
	return stack;
}

int isEmpty(ExamPaper *stack){
	if (stack == NULL) return 1;
	return 0;
}

void display_exam(ExamPaper *stack){
	ExamPaper *tmp = stack;
	if (tmp == NULL)
	{
		printf("Stack is empty\n");
		return;
	}
	printf("Exam Papers in the Stack:\n");
	while (tmp != NULL)
	{
		printf("Student Name : %s ,", tmp->stu_name);
		printf("Student Number : %ld ,", tmp->stu_number);
		printf("Score : %d \n", tmp->score);
		tmp = tmp->next;
	}
	printf("\n");
}

void free_exam_paper(ExamPaper *stack){
	ExamPaper *tmp = stack;
	while (tmp != NULL)
	{
		stack = stack->next;
		free(tmp->stu_name);
		free(tmp);
		tmp = stack;
	}
}

void free_order(Order *stack)
{
	Order *tmp = stack;
	while (tmp != NULL)
	{
		stack = stack->next;
		free(tmp->cus_name);
		free(tmp->food);
		free(tmp->order_time);
		free(tmp);
		tmp = stack;
	}
}
