# 🔧 Derleyici ayarları
CC = gcc
CFLAGS = -Wall -Iinclude -Iserver -Iclient -Iipc -g
LDFLAGS = -lrt -pthread
#THREAD_CFLAGS = -fsanitize=thread -pthread

# 📂 Klasör tanımları
OBJ_DIR = obj
SRC_SERVER = server
SRC_CLIENT = client
SRC_IPC = ipc

# 📄 Kaynak dosyaları
SERVER_SRC_FILES = bank_server.c database.c teller_api.c teller.c utils.c
CLIENT_SRC_FILES = bank_client.c
IPC_SRC_FILES = fifo_utils.c shm_utils.c

# 📁 Objeye dönüştürülmüş dosyalar
SERVER_OBJ = $(addprefix $(OBJ_DIR)/, $(SERVER_SRC_FILES:.c=.o))
CLIENT_OBJ = $(addprefix $(OBJ_DIR)/, $(CLIENT_SRC_FILES:.c=.o))
IPC_OBJ = $(addprefix $(OBJ_DIR)/, $(IPC_SRC_FILES:.c=.o))

# 🔨 Derlenecek ikililer
SERVER_BIN = BankServer
CLIENT_BIN = BankClient

# 🎯 Varsayılan hedef
all: $(OBJ_DIR) $(SERVER_BIN) $(CLIENT_BIN)
	@echo ""
	@echo "\033[1;33m Program Usage \033[0m"
	@echo ""
	@echo "\033[1;32mServer:\033[0m"
	@echo "  \033[1;36m./BankServer BankName\033[0m"
	@echo "    ➔ Example: \033[1;34m./BankServer AdaBank\033[0m"
	@echo ""
	@echo "\033[1;32mClient:\033[0m"
	@echo "  \033[1;36m./BankClient ClientFileXX.file\033[0m"
	@echo "    ➔ Example: \033[1;34m./BankClient Client01.file\033[0m"
	@echo ""

# 📦 obj klasörünü oluştur
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# 🏦 Sunucu derlemesi
$(SERVER_BIN): $(SERVER_OBJ) $(IPC_OBJ)
	@echo "\033[1;32m[Linking]\033[0m $@"
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# 👤 Client derlemesi
$(CLIENT_BIN): $(CLIENT_OBJ) $(OBJ_DIR)/fifo_utils.o
	@echo "\033[1;32m[Linking]\033[0m $@"
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# 📄 Tüm .c dosyalarını obj/ altına derle
$(OBJ_DIR)/%.o: $(SRC_SERVER)/%.c
	@echo "\033[1;34m[Compiling Server]\033[0m $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_CLIENT)/%.c
	@echo "\033[1;36m[Compiling Client]\033[0m $<"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_IPC)/%.c
	@echo "\033[1;35m[Compiling IPC]\033[0m $<"
	$(CC) $(CFLAGS) -c $< -o $@

# 🧹 Temizlik hedefi
clean:
	@echo "\033[1;31m[Cleaning]\033[0m removing binaries and objects..."
	@rm -rf $(OBJ_DIR) $(SERVER_BIN) $(CLIENT_BIN)

# 🔁 Yeniden derleme
re: clean all

.PHONY: all clean re usage
