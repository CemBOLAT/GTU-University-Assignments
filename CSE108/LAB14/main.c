#include "util.h"

int main()
{
	Order *list = NULL;

	enqueue(&list, "Ali Yılmaz", 101, "Pizza, Salad, Ice Cream", time(NULL));
	enqueue(&list, "Ayşe Demir", 102, "Steak, Mashed Potatoes, Salad", time(NULL));

	time_t thresholdTime = time(NULL);
	list = dequeue(list, thresholdTime);

	LIFO stack;
	stack.top = list;
	serializeLIFO(&stack, LIFO_FILE);

	LIFO *deserializedLIFO = deserializeLIFO(LIFO_FILE);
	displayLIFO(deserializedLIFO);
	f_draw_line();

	FIFO queue;
	queue.head = list;
	queue.tail = list->next;
	serializeFIFO(&queue, FIFO_FILE);

	FIFO *deserializedFIFO = deserializeFIFO(FIFO_FILE);
	displayFIFO(deserializedFIFO);
	f_draw_line();

	return 0;
}

void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}
