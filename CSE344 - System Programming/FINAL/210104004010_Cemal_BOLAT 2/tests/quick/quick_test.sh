#!/bin/bash

# Quick Test Script for Chat Server
# Bu script temel fonksiyonaliteyi hızlıca test eder

# Renkler
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Konfigürasyon
SERVER_IP="127.0.0.1"
SERVER_PORT="8080"
ROOM_NAME="quicktest"
TEST_DURATION=45  # Increased from 30 to 45 seconds

echo -e "${GREEN}=== Quick Chat Server Test ===${NC}"
echo -e "${YELLOW}This test will run for $TEST_DURATION seconds with 5 users${NC}"
echo ""

# Executable kontrolü
if [ ! -f "./chatserver" ] || [ ! -f "./chatclient" ]; then
    echo -e "${RED}Error: chatserver or chatclient executable not found!${NC}"
    echo -e "${YELLOW}Please compile first with: make${NC}"
    exit 1
fi

# Server PID
SERVER_PID=""

# Cleanup function
cleanup() {
    echo -e "\n${YELLOW}Cleaning up...${NC}"
    
    if [ ! -z "$SERVER_PID" ] && kill -0 "$SERVER_PID" 2>/dev/null; then
        kill "$SERVER_PID" 2>/dev/null
        sleep 2
    fi
    
    pkill -f "chatclient.*$SERVER_PORT" 2>/dev/null
    pkill -f "chatserver.*$SERVER_PORT" 2>/dev/null
    
    echo -e "${GREEN}Quick test completed!${NC}"
    exit 0
}

trap cleanup SIGINT

# Server başlat
echo -e "${BLUE}Starting server...${NC}"
./chatserver $SERVER_PORT > quick_server.log 2>&1 &
SERVER_PID=$!

# Server'ın başlamasını bekle
sleep 3

if ! netstat -tuln 2>/dev/null | grep -q ":$SERVER_PORT " && ! ss -tuln 2>/dev/null | grep -q ":$SERVER_PORT "; then
    echo -e "${RED}Error: Server failed to start!${NC}"
    exit 1
fi

echo -e "${GREEN}Server started!${NC}"

# 5 client başlat
USERS=("Alice" "Bob" "Jj" "Diana" "Eve")

# Senkronizasyon için dosya oluştur
SYNC_FILE="/tmp/chat_sync_$$"
touch "$SYNC_FILE"

for i in "${!USERS[@]}"; do
    username="${USERS[$i]}"
    echo -e "${BLUE}Starting client: $username${NC}"
    
    (
        sleep $((i * 2))
        {
            echo "$username"
            sleep 3  # Increased from 2 to 3 seconds
            echo "/join $ROOM_NAME"
            sleep 2
            echo "/broadcast Merhaba, ben $username!"
            sleep 5
            
            # Senkronizasyon: Herkes katıldıktan sonra devam et
            echo "1" >> "$SYNC_FILE"
            while [ $(wc -l < "$SYNC_FILE") -lt ${#USERS[@]} ]; do
                sleep 1
            done
            
            case $i in
                0) echo "/whisper Bob Merhaba Bob!" ;;
                1) echo "/broadcast Bob burada!" ;;
                2) echo "/broadcast Hepsi burada!" ;;
                3) echo "/broadcast Jj katıldı!" ;;
                4) echo "/whisper Alice Selam Alice!" ;;
            esac
            
            sleep 15  # Increased from 10 to 15 seconds
            echo "/leave"
            sleep 2  # Increased from 1 to 2 seconds
            echo "/exit"
            
        } | ./chatclient $SERVER_IP $SERVER_PORT > "quick_client_${username}.log" 2>&1
    ) &
    
    sleep 1
done

echo -e "${GREEN}All clients started!${NC}"
echo -e "${YELLOW}Test running for $TEST_DURATION seconds...${NC}"

# Test süresi kadar bekle
sleep $TEST_DURATION

echo -e "${GREEN}Test completed! Checking results...${NC}"

# Basit analiz
if [ -f "server.log" ]; then
    echo ""
    echo -e "${BLUE}=== Quick Test Results ===${NC}"
    echo "Logins: $(grep -c "\[LOGIN\]" server.log)"
    echo "Broadcasts: $(grep -c "\[BROADCAST\]" server.log)"
    echo "Whispers: $(grep -c "\[WHISPER\]" server.log)"
    echo "Room joins: $(grep -c "joined" server.log)"
    echo ""
    echo -e "${YELLOW}Check quick_server.log and quick_client_*.log for details${NC}"
fi

# Senkronizasyon dosyasını temizle
rm -f "$SYNC_FILE"

cleanup 