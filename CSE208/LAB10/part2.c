#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 10
#define LINE '-'
#define CAR 'C'
#define FINISH 'F'
#define EMPTY '.'
#define FLUSH while(getchar() != '\n')

typedef struct b_block{
    int cost;
    int type; 
} block;

int randomGenerator(int max);
void initBoard(block board[SIZE][SIZE]);
void printBoard(block board[SIZE][SIZE]);
void printMoves(char moves[]);
void gamePlay(block board[SIZE][SIZE], char moves[]);
void assignCar(block board[SIZE][SIZE], int *x, int *y);
void gamePlay(block board[SIZE][SIZE], char moves[]);

int main(){
    block board[SIZE][SIZE];
    char moves[1000];
    for (int i = 0; i < 1000; i++){
        moves[i] = '\0';
    }
    srand(time(NULL));
    initBoard(board);
    printBoard(board);
    gamePlay(board, moves);
    return 0;
}

void gamePlay(block board[SIZE][SIZE], char moves[]){
    int m = -1;
    int carX, carY;
    
    assignCar(board, &carX, &carY);
    int totalCost = 0;
    while(1){
        char move;
        printf("Enter your move: w, s, a, d and 'r' for run : ");
        scanf(" %c", &move);
        FLUSH;
        m++;
        if (move == 'r'){
            break;
        }
        else if (move == 'w'){
            if (carY == 0 || board[carY - 1][carX].type == LINE || board[carY - 1][carX].type == CAR){
                printf("Invalid move\n");
                m--;
                continue;
            }
            moves[m] = '^';
            carY--;
        }
        else if (move == 's'){
            if (carY == SIZE - 1 || board[carY + 1][carX].type == LINE || board[carY + 1][carX].type == CAR){
                printf("Invalid move\n");
                m--;
                continue;
            }
            moves[m] = 'v';
            carY++;
        }
        else if (move == 'a'){
            if (carX == 0 || board[carY][carX - 1].type == LINE || board[carY][carX - 1].type == CAR){
                printf("Invalid move\n");
                m--;
                continue;
            }
            moves[m] = '<';
            carX--;
        }
        else if (move == 'd'){
            if (carX == SIZE - 1 || board[carY][carX + 1].type == LINE || board[carY][carX + 1].type == CAR){
                printf("Invalid move\n");
                m--;
                continue;
            }
            moves[m] = '>';
            carX++;
        }
        else{
            printf("Invalid move\n");
            m--;
        }
        if (board[carY][carX].type == FINISH){
            break;
        }
        board[carY][carX].type = LINE;
        totalCost += board[carY][carX].cost;

        printBoard(board);
        printf("*********************************\n");
        printMoves(moves);
    }
    moves[m] = '\0';
    if (board[carY][carX].type == FINISH){
        printf("You won\n");
    }
    else{
        printf("You lost try again!\n");
    }
    printf("Total cost: %d\n", totalCost);
}

void printMoves(char moves[]){
    int i = 0;
    while(moves[i] != '\0'){
        printf("%c ", moves[i]);
        i++;
    }
    printf("\n");
}

void assignCar(block board[SIZE][SIZE], int *x, int *y){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            if (board[i][j].type == CAR){
                *x = j;
                *y = i;
                return;
            }
        }
    }
}

void printBoard(block board[SIZE][SIZE]){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            printf("%c ", board[i][j].type);
        }
        printf("\n");
    }
}

void initBoard(block board[SIZE][SIZE]){
    int i, j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < SIZE; j++){
            board[i][j].cost = randomGenerator(10);
            board[i][j].type = '.';
        }
    }
    int start = randomGenerator(100);
    int finish = randomGenerator(100);
    while (start == finish){
        finish = randomGenerator(100);
    }
    board[start / 10][start % 10].type = CAR;
    board[start / 10][start % 10].cost = 0;
    board[finish / 10][finish % 10].type = FINISH;
    board[finish / 10][finish % 10].cost = 0;
}

int randomGenerator(int max) {
    return rand() % max;
}