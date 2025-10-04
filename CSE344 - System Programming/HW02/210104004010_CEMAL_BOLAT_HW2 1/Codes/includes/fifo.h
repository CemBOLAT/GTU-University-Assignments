#ifndef FIFO_H
#define FIFO_H

int create_fifo(const char *fifo);
int send_to_fifo(const char *fifo, int num1, int num2, int is_first);
int receive_from_fifo(const char *fifo, int *values, int is_first);

#endif
