NAME := chess # Exec
SRC :=	./src/Pieces.cpp \
		./src/main.cpp \
		./src/Chess.cpp \
		./src/Board.cpp

FLAGS := -pedantic -std=c++11 -Wall -Wextra -Werror
DEBUG := -fsanitize=address

OBJ := ./obj/Pieces.o \
		./obj/Board.o \
		./obj/main.o \
		./obj/Chess.o \


# ANSI renk kodları
GREEN = \033[0;32m
YELLOW = \033[1;33m
RESET = \033[0m
all: $(NAME)
	@echo "$(GREEN)Game Compiled$(RESET). You can read readme file with '$(YELLOW)make readme$(RESET)'"

readme: ./readme/readme.txt
	@cat ./readme/readme.txt

$(NAME): $(OBJ)
	g++ $(FLAGS) $(OBJ) -o $(NAME)

debug: $(OBJ)
	@g++ $(FLAGS) $(DEBUG) $(OBJ) -o $(NAME)

./obj/%.o: ./src/%.cpp
	@g++ $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all readme
