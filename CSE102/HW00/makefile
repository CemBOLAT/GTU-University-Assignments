all: clean compile run

compile: main.c util.c util.h
	@echo "\033[33m-------------------------------------------"
	@echo "Compiling...\033[36m"
	@gcc -o test main.c util.c

run:
	@echo "-------------------------------------------"
	@echo "\033[36mRunning the tests...."
	@echo "================================================================================="
	@echo "\033[32m./test\033[0m"
	@./test
	@echo "\033[32m================================================================================="
	@echo "[SUCCESS] Completed tests....\033[0m"

clean:
	@echo "\033[34m-------------------------------------------"
	@echo "Removing compiled files...\033[0m"
	@rm -f *.o
	@rm -f test
