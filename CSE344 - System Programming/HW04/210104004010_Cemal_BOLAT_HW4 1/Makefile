CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS = -lpthread

SRC = 210104004010_main.c buffer.c utils.c
OBJ = $(SRC:.c=.o)
TARGET = LogAnalyzer
USAGE = "Usage: ./LogAnalyzer <buffer_size> <num_workers> <log_file> <search_term>"

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "\033[1;32mCompilation complete. Run the program with the following command:\033[0m"
	@echo "\033[1;33m./$(TARGET) <buffer_size> <num_workers> <log_file> <search_term>\033[0m"
	@echo "\033[1;36mExample: ./LogAnalyzer 10 4 ./logs/deneme.log error\033[0m"

clean:
	rm -f $(TARGET) *.o

re: clean all

.PHONY: all clean re