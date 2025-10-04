CC = gcc
CFLAGS = -Iincludes -Wall -Wextra -Werror -g

THREAD = -lpthread
SRCDIR = src
INCDIR = includes
OBJDIR = obj
BINDIR = bin

LOGFILE = /tmp/daemon.log

EXEC = SatelliteSystem

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(THREAD)

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
