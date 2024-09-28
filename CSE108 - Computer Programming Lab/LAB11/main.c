#include "util.h"

void	fifo(void){
	int		input;
	Order	*head = NULL;

	printf("\n");
	
	head = enqueue(head, "Zehra Bilici", 101, "Pizza, Salad, Ice Cream", "2 June 2021 12:00");
	head = enqueue(head, "Barış Ozcam", 102, "Burger, Fries, Coke", "2 June 2021 12:00");
	head = enqueue(head, "Mehmet Burak Koca", 103, "Steak, Mashed Potatoes, Salad", "2 June 2021 12:10");

	display(head);
	head = dequeue(head);
	display(head);
	head = dequeue(head);
	display(head);
	updateOrder(head, 103, "Steak, Mashed Potatoes, Salad, Coke");
	display(head);
	free_order(head);
}


void	lifo(void){
	int			input;
	ExamPaper	*stack = NULL;

	if (isEmpty(stack)) printf("\nStack is empty\n\n");
	else printf("\nStack is not empty\n\n");

	stack = push(stack, "Zehra Bilici", 20220000001, 90);
	stack = push(stack, "Barış Özcan", 20190000002, 85);
	stack = push(stack, "Mehmet Burak Koca", 20180000010, 95);

	if (isEmpty(stack)) printf("\nStack is empty\n\n");
	else printf("\nStack is not empty\n\n");

	display_exam(stack);
	stack = pop(stack);
	display_exam(stack);

	free_exam_paper(stack);
}

int main(){

	int input;

	do {
		printf("\nEnter 0 to FIFO or 1 to LIFO: ");
		scanf("%d", &input);
		if (input != 0 && input != 1)
			printf("Invalid input\n");
	} while (input != 0 && input != 1);

	switch (input)
	{
		case 0: fifo(); break;
		case 1: lifo(); break;
	}
}
