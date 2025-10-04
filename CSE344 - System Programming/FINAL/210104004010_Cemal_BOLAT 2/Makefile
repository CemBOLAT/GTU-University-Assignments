# Compiler and Flags
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror #-pthread

# Paths
SERVER_DIR = server
CLIENT_DIR = client
BIN_SERVER = chatserver
BIN_CLIENT = chatclient
TEST_WSL_DIR = tests/wsl
TEST_QUICK_DIR = tests/quick
TEST_FILES_DIR = tests/file

# Source and Object files
SERVER_SRC = $(wildcard $(SERVER_DIR)/*.c)
CLIENT_SRC = $(wildcard $(CLIENT_DIR)/*.c)
SERVER_OBJ = $(SERVER_SRC:.c=.o)
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)

# Rule: all
all: $(BIN_SERVER) $(BIN_CLIENT) copy_to_tests

# Rule: server executable
$(BIN_SERVER): $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

server: $(BIN_SERVER)
client: $(BIN_CLIENT)

# Rule: client executable
$(BIN_CLIENT): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Rule: compile .c to .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule: copy executables to test directories
copy_to_tests: $(BIN_SERVER) $(BIN_CLIENT)
	@echo "Copying executables to test directories..."
	@mkdir -p $(TEST_WSL_DIR)
	@mkdir -p $(TEST_QUICK_DIR)
	@mkdir -p $(TEST_FILES_DIR)
	@cp -f $(BIN_SERVER) $(TEST_WSL_DIR)/
	@cp -f $(BIN_CLIENT) $(TEST_WSL_DIR)/
	@cp -f $(BIN_SERVER) $(TEST_QUICK_DIR)/
	@cp -f $(BIN_CLIENT) $(TEST_QUICK_DIR)/
	@cp -f $(BIN_SERVER) $(TEST_FILES_DIR)/
	@cp -f $(BIN_CLIENT) $(TEST_FILES_DIR)/
	@echo "Executables copied to $(TEST_WSL_DIR)/ and $(TEST_QUICK_DIR)/ and $(TEST_FILES_DIR)/"

# Rule: clean
clean: clean_tests
	rm -f $(BIN_SERVER) $(BIN_CLIENT) $(SERVER_DIR)/*.o $(CLIENT_DIR)/*.o

# Rule: clean test directories
clean_tests:
	rm -f $(TEST_WSL_DIR)/$(BIN_SERVER) $(TEST_WSL_DIR)/$(BIN_CLIENT)
	rm -f $(TEST_QUICK_DIR)/$(BIN_SERVER) $(TEST_QUICK_DIR)/$(BIN_CLIENT) $(TEST_FILES_DIR)/$(BIN_SERVER) $(TEST_FILES_DIR)/$(BIN_CLIENT)
	@echo "Test executables removed from test directories"

# Rule: force rebuild
re: clean all

# Rule: force rebuild and copy
rebuild: clean all copy_to_tests

.PHONY: all clean re copy_to_tests clean_tests rebuild
