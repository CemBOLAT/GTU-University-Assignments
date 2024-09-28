#include "util.h"

void enqueue(Order **list, char *customerName, int orderID, char *items, time_t orderTime)
{
	Order *newOrder = (Order *)malloc(sizeof(Order));

	newOrder->customerName = strdup(customerName);
	newOrder->items = strdup(items);
	newOrder->orderID = orderID;
	newOrder->orderTime = orderTime;
	newOrder->next = NULL;

	if (*list == NULL) *list = newOrder;
	else
	{
		Order *head = *list;
		while (head->next != NULL) head = head->next;
		head->next = newOrder;
	}
	printf("Order Added: ");
	displayOrder(newOrder);
}

Order *dequeue(Order *queue, time_t thresholdTime)
{
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
	if (prev == NULL)
		queue = NULL;
	else
		prev->next = NULL;
	printf("Order Deleted: ");
	displayOrder(tmp);
	free(tmp);
	return queue;
}

void displayOrder(Order *order)
{
	printf("Customer Name: %s, Order ID: %d, Items: %s, Order Time: %s", order->customerName, order->orderID, order->items, ctime(&order->orderTime));
}

void displayLIFO(LIFO *stack)
{
	Order *temp = stack->top;
	printf("LIFO Data Structure:\n");
	while (temp != NULL)
	{
		displayOrder(temp);
		temp = temp->next;
	}
}

void displayFIFO(FIFO *queue)
{
	Order *temp = queue->head;
	printf("FIFO Data Structure:\n");
	while (temp != NULL)
	{
		displayOrder(temp);
		temp = temp->next;
	}
}
