name := hw1
src := $(wildcard *.c)

all: $(name)

$(name): $(src)
	@gcc -o $(name) $(src) -lm

clean:
	@rm -f $(name)

run: $(name)
	@./$(name)

re : clean all

valgrind: $(name)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(name)

.PHONY: all clean
