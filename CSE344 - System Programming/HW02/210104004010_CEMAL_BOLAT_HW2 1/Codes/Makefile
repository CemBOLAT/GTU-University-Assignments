CC = gcc
CFLAGS = -Iincludes -Wall -Wextra -Werror -g

SRCDIR = src
INCDIR = includes
OBJDIR = obj
BINDIR = bin

LOGFILE = /tmp/daemon.log

EXEC = ipc
MSG = "To run the program use:\\nmake run \\n./$(EXEC) \<int1\> \<int2\>"

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(EXEC)
	@echo "\033[33m$(MSG)\033[0m"

run: $(EXEC)
	@echo "./$(EXEC) 1 2"
	@./$(EXEC) 1 2

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)

distclean: clean
	rm -rf $(EXEC)

re: distclean all

.PHONY: all clean distclean re
