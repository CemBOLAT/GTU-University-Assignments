NAME=lab4

all: clean compile run

compile: main.c util.h
	@echo "\033[33m-------------------------------------------"
	@echo "Compiling...\033[36m"
	@gcc -o $(NAME) main.c

run:
	@echo "-------------------------------------------"
	@echo "\033[36mRunning the program...."
	@echo "================================================================================="
	@echo "\033[32m./${NAME}\033[0m"
	@./${NAME}
	@echo "\033[32m================================================================================="
	@echo "[SUCCESS] Completed tests....\033[0m"

clean:
	@echo "\033[34m-------------------------------------------"
	@echo "Removing compiled files...\033[0m"
	@rm -f *.o
	@rm -f $(NAME)
.PHONY: all, compile, run, clean
