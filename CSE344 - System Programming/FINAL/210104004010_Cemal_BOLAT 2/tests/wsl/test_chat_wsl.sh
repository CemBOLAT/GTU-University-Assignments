#!/bin/bash

# Chat Server Test Script for WSL
# Bu script WSL ortamında çalışacak şekilde optimize edilmiştir
# 30 farklı client ile test senaryosu çalıştırır

# Renkler
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Konfigürasyon
SERVER_IP="127.0.0.1"
SERVER_PORT="8080"
ROOM_NAME="testroom"

# Senkronizasyon için dosya
SYNC_FILE="/tmp/chat_sync_$$"
touch "$SYNC_FILE"

# 30 kullanıcı ismi
USERS=(
    "Alice" "Bob" "Charlie" "Diana" "Eve" "Frank" "Grace" "Henry" "Ivy" "Jack"
    "Kate" "Liam" "Mia" "Noah" "Olivia" "Paul" "Quinn" "Ruby" "Sam" "Tina"
    "Uma" "Victor" "Wendy" "Xander" "Yara" "Zoe" "Alex" "Beth" "Carl" "Dana"
)

echo -e "${GREEN}=== Chat Server Test Script for WSL ===${NC}"
echo -e "${YELLOW}Server IP: $SERVER_IP${NC}"
echo -e "${YELLOW}Server Port: $SERVER_PORT${NC}"
echo -e "${YELLOW}Test Room: $ROOM_NAME${NC}"
echo -e "${YELLOW}Number of clients: ${#USERS[@]}${NC}"
echo ""

# WSL ortamını kontrol et
if grep -qi microsoft /proc/version 2>/dev/null; then
    echo -e "${GREEN}WSL environment detected!${NC}"
    WSL_MODE=true
else
    echo -e "${YELLOW}Not running in WSL${NC}"
    WSL_MODE=false
fi

# Executable'ların varlığını kontrol et
if [ ! -f "./chatserver" ]; then
    echo -e "${RED}Error: chatserver executable not found!${NC}"
    echo -e "${YELLOW}Please compile first with: make${NC}"
    exit 1
fi

if [ ! -f "./chatclient" ]; then
    echo -e "${RED}Error: chatclient executable not found!${NC}"
    echo -e "${YELLOW}Please compile first with: make${NC}"
    exit 1
fi

echo -e "${GREEN}All requirements found!${NC}"

# Server PID'ini saklamak için
SERVER_PID=""
declare -a CLIENT_PIDS

# Cleanup function
cleanup() {
    echo -e "\n${YELLOW}Cleaning up...${NC}"
    
    # Kill all client processes
    for pid in "${CLIENT_PIDS[@]}"; do
        if kill -0 "$pid" 2>/dev/null; then
            kill "$pid" 2>/dev/null
        fi
    done
    
    # Kill server if running
    if [ ! -z "$SERVER_PID" ] && kill -0 "$SERVER_PID" 2>/dev/null; then
        echo -e "${YELLOW}Stopping server (PID: $SERVER_PID)...${NC}"
        kill "$SERVER_PID" 2>/dev/null
        sleep 2
        # Force kill if still running
        if kill -0 "$SERVER_PID" 2>/dev/null; then
            kill -9 "$SERVER_PID" 2>/dev/null
        fi
    fi
    
    # Kill any remaining processes
    pkill -f "chatclient.*$SERVER_PORT" 2>/dev/null
    pkill -f "chatserver.*$SERVER_PORT" 2>/dev/null
    
    # Senkronizasyon dosyasını temizle
    rm -f "$SYNC_FILE"
    
    wait 2>/dev/null
    echo -e "${GREEN}Cleanup completed.${NC}"
    exit 0
}

# Trap SIGINT (Ctrl+C) to cleanup
trap cleanup SIGINT

# Server başlatma
echo -e "${BLUE}Starting chat server...${NC}"
echo -e "${YELLOW}You can choose how to start the server:${NC}"
echo -e "${YELLOW}1. Background mode (recommended for WSL)${NC}"
echo -e "${YELLOW}2. Separate terminal (if X11 forwarding works)${NC}"
echo -e "${YELLOW}3. Manual start (you start server yourself)${NC}"
echo ""
read -p "Enter choice (1-3): " choice

case $choice in
    1)
        echo -e "${BLUE}Starting server in background mode...${NC}"
        ./chatserver $SERVER_PORT > server_wsl.log 2>&1 &
        SERVER_PID=$!
        echo -e "${YELLOW}Server started with PID: $SERVER_PID${NC}"
        echo -e "${YELLOW}Server output is being logged to server_wsl.log${NC}"
        sleep 3
        ;;
        
    2)
        echo -e "${BLUE}Attempting to start server in separate terminal...${NC}"
        if [ "$WSL_MODE" = true ]; then
            # WSL için X11 forwarding kontrol et
            if [ -z "$DISPLAY" ]; then
                export DISPLAY=:0
            fi
            
            # Windows Terminal kullanmayı dene
            if command -v wt.exe &> /dev/null; then
                wt.exe new-tab --title "Chat Server" bash -c "cd '$(pwd)'; ./chatserver $SERVER_PORT 2>&1 | tee server_wsl.log; read" &
            elif command -v gnome-terminal &> /dev/null; then
                gnome-terminal --title="Chat Server" -- bash -c "./chatserver $SERVER_PORT 2>&1 | tee server_wsl.log; read" &
            else
                echo -e "${YELLOW}No suitable terminal found, falling back to background mode...${NC}"
                ./chatserver $SERVER_PORT > server_wsl.log 2>&1 &
                SERVER_PID=$!
            fi
        else
            gnome-terminal --title="Chat Server" -- bash -c "./chatserver $SERVER_PORT 2>&1 | tee server_wsl.log; read" &
        fi
        sleep 5
        ;;
        
    3)
        echo -e "${YELLOW}Please start the server manually in another terminal:${NC}"
        echo -e "${BLUE}./chatserver $SERVER_PORT${NC}"
        echo ""
        echo -e "${YELLOW}Press Enter when server is running...${NC}"
        read
        ;;
        
    *)
        echo -e "${RED}Invalid choice. Using background mode.${NC}"
        ./chatserver $SERVER_PORT > server_wsl.log 2>&1 &
        SERVER_PID=$!
        sleep 3
        ;;
esac

# Server'ın çalışıp çalışmadığını kontrol et
echo -e "${BLUE}Checking if server is running...${NC}"
for i in {1..15}; do
    if netstat -tuln 2>/dev/null | grep -q ":$SERVER_PORT " || ss -tuln 2>/dev/null | grep -q ":$SERVER_PORT "; then
        echo -e "${GREEN}Server is running on port $SERVER_PORT!${NC}"
        break
    fi
    if [ $i -eq 15 ]; then
        echo -e "${RED}Error: Server is not responding on port $SERVER_PORT${NC}"
        echo -e "${YELLOW}Please check:${NC}"
        echo -e "${YELLOW}1. Server started successfully${NC}"
        echo -e "${YELLOW}2. Port $SERVER_PORT is not in use${NC}"
        echo -e "${YELLOW}3. Check server_wsl.log for errors${NC}"
        if [ -f "server_wsl.log" ]; then
            echo -e "${YELLOW}Last few lines of server log:${NC}"
            tail -5 server_wsl.log
        fi
        exit 1
    fi
    echo -e "${YELLOW}Waiting for server... ($i/15)${NC}"
    sleep 2
done

echo ""

# Client başlatma fonksiyonu
start_client() {
    local username=$1
    local client_id=$2
    local delay=$3
    
    echo -e "${BLUE}Starting client for user: $username${NC}"
    
    # Client'ı background'da başlat
    (
        sleep $delay
        echo -e "${GREEN}[$username] Connecting to server...${NC}"
        
        # Client'a komutları gönder
        {
            echo "$username"  # Kullanıcı adı gir
            sleep 2
            echo "/join $ROOM_NAME"  # Odaya katıl
            sleep 2
            echo "/broadcast Merhaba, ben $username! (Client #$client_id)"  # İlk mesaj
            
            # Senkronizasyon: Herkes katıldıktan sonra devam et
            echo "1" >> "$SYNC_FILE"
            while [ $(wc -l < "$SYNC_FILE") -lt ${#USERS[@]} ]; do
                sleep 1
            done
            
            # Rastgele mesajlar gönder
            case $((client_id % 5)) in
                0)
                    sleep 3
                    echo "/broadcast $username: Herkese selam!"
                    sleep 5
                    echo "/broadcast $username: Nasıl gidiyor?"
                    ;;
                1)
                    sleep 4
                    echo "/broadcast $username: Ben de katıldım!"
                    sleep 4
                    echo "/broadcast $username: Güzel bir grup olmuş!"
                    ;;
                2)
                    sleep 5
                    echo "/broadcast $username: Merhaba arkadaşlar!"
                    sleep 3
                    echo "/broadcast $username: Test çok iyi gidiyor!"
                    ;;
                3)
                    sleep 6
                    echo "/broadcast $username: Selam herkese!"
                    sleep 4
                    echo "/broadcast $username: 30 kişi çok kalabalık :)"
                    ;;
                4)
                    sleep 7
                    echo "/broadcast $username: Son katılanlardan biriyim!"
                    sleep 3
                    echo "/broadcast $username: Harika bir test!"
                    ;;
            esac
            
            # Bazı kullanıcılar whisper mesajı göndersin
            if [ $((client_id % 3)) -eq 0 ] && [ $client_id -gt 3 ]; then
                target_idx=$((client_id % 10))
                target_user="${USERS[$target_idx]}"
                sleep 2
                echo "/whisper $target_user Merhaba $target_user, ben $username!"
            fi
            
            # Biraz bekle sonra çık
            sleep 15
            echo "/leave"
            sleep 2
            echo "/exit"
            
        } | ./chatclient $SERVER_IP $SERVER_PORT > "client_${username}.log" 2>&1
        
        echo -e "${YELLOW}[$username] Client finished.${NC}"
        
    ) &
    
    # Process ID'yi sakla
    CLIENT_PIDS[$client_id]=$!
}

echo -e "${GREEN}Starting ${#USERS[@]} clients...${NC}"
echo ""

# 30 client'ı sırayla başlat
for i in "${!USERS[@]}"; do
    client_id=$((i + 1))
    username="${USERS[$i]}"
    delay=$((i * 1))  # Her client 1 saniye arayla başlasın
    
    start_client "$username" "$client_id" "$delay"
    sleep 0.5
done

echo -e "${GREEN}All ${#USERS[@]} clients started!${NC}"
echo -e "${YELLOW}Test scenario is running...${NC}"
echo -e "${YELLOW}Each client will run for about 30 seconds${NC}"
echo ""
echo -e "${BLUE}You can monitor:${NC}"
echo -e "${BLUE}  - Server output: tail -f server_wsl.log${NC}"
echo -e "${BLUE}  - Client logs: client_<username>.log${NC}"
echo -e "${BLUE}  - Real-time server activity: watch 'tail -10 server_wsl.log'${NC}"
echo ""
echo -e "${YELLOW}Press Ctrl+C to stop all clients and server${NC}"
echo -e "${YELLOW}Or wait for all clients to finish naturally...${NC}"

# Tüm client'ların bitmesini bekle
echo ""
echo -e "${BLUE}Waiting for all clients to finish...${NC}"
for pid in "${CLIENT_PIDS[@]}"; do
    wait $pid 2>/dev/null
done

echo ""
echo -e "${GREEN}=== Test Completed! ===${NC}"

# Server'ı durdur
if [ ! -z "$SERVER_PID" ] && kill -0 "$SERVER_PID" 2>/dev/null; then
    echo -e "${YELLOW}Stopping server...${NC}"
    kill "$SERVER_PID" 2>/dev/null
    sleep 2
fi

echo ""
echo -e "${YELLOW}Generated log files:${NC}"
echo -e "${BLUE}  - server_wsl.log (server output)${NC}"
for user in "${USERS[@]}"; do
    if [ -f "client_${user}.log" ]; then
        echo -e "${BLUE}  - client_${user}.log${NC}"
    fi
done

echo ""
echo -e "${YELLOW}You can also check the main server log: server.log${NC}"
echo -e "${GREEN}WSL test script finished successfully!${NC}" 