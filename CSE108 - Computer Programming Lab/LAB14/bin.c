#include "util.h"

void serializeLIFO(LIFO *stack, const char *filename)
{
	FILE *file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("Error opening file for serialization.\n");
		return;
	}

	Order *temp = stack->top;
	while (temp != NULL)
	{
		fwrite(temp, sizeof(Order), 1, file);
		temp = temp->next;
	}

	fclose(file);
	printf("LIFO data structure serialized to a binary file.\n");
}

LIFO *deserializeLIFO(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("Error opening file for deserialization.\n");
		return NULL;
	}

	LIFO *stack = (LIFO *)malloc(sizeof(LIFO));
	stack->top = NULL;

	Order *prev = NULL;
	Order *temp;

	while (!feof(file))
	{
		temp = (Order *)malloc(sizeof(Order));
		if (fread(temp, sizeof(Order), 1, file) != 1)
		{
			free(temp);
			break;
		}
		temp->next = NULL;

		if (stack->top == NULL) stack->top = temp;
		else prev->next = temp;
		prev = temp;
	}

	fclose(file);
	printf("LIFO data structure deserialized from a binary file.\n");
	return stack;
}

void serializeFIFO(FIFO *queue, const char *filename)
{
	FILE *file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("Error opening file for serialization.\n");
		return;
	}

	Order *head = queue->head;
	while (head != NULL)
	{
		fwrite(head, sizeof(Order), 1, file);
		head = head->next;
	}

	fclose(file);
	printf("FIFO data structure serialized to a binary file.\n");
}

FIFO *deserializeFIFO(const char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("Error opening file for deserialization.\n");
		return NULL;
	}

	FIFO *queue = (FIFO *)malloc(sizeof(FIFO));
	queue->head = NULL;
	queue->tail = NULL;

	Order *prev = NULL;
	Order *temp;

	while (!feof(file))
	{
		temp = (Order *)malloc(sizeof(Order));
		if (fread(temp, sizeof(Order), 1, file) != 1)
		{
			free(temp);
			break;
		}
		temp->next = NULL;

		if (queue->head == NULL) queue->head = temp;
		else prev->next = temp;
		prev = temp;
		queue->tail = temp;
	}

	fclose(file);
	printf("FIFO data structure deserialized from a binary file.\n");
	return queue;
}
