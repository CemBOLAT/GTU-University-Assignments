# I declare variable in Makefile. When I used with $ sign and parentheses as $(NAME) <in my example> system uses its value
NAME=hw07
# * means anything after the * I used "*.c" that means it must ends with ".c"
SRC=*.c
all: clean compile

compile: $(SRC)
	@echo "\033[33m-------------------------------------------"
	@echo "Compiling...\033[36m"
	@gcc -o $(NAME) $(SRC) -lm
	@echo "\033[32m >> Usage: ./$(NAME) <word1> <word2> <word3> ... <word100>\033[36m"

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
