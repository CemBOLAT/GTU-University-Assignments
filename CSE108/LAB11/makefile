# I declare variable in Makefile. When I used with $ sign and parentheses as $(NAME) <in my example> system uses its value
NAME=lab11
# * means anything after the * I used "*.c" that means it must ends with ".c"
SRC=*.c
all: clean compile run

compile: $(SRC)
	@echo "\033[33m-------------------------------------------"
	@echo "Compiling...\033[36m"
	@gcc -o $(NAME) $(SRC) -lm

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
# I used .PHONY rule to declare as function
# I mean when I use <compile> rule in this makefile I need requirements which are main.c part1.c ...
# Before the checking requirements system checks does this folder has a file or folder as rules name <compile> in this example
# To ignore that I add .PHONY rule thats why I mentioned it as a function
