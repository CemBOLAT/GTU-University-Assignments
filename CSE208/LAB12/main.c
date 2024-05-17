
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "input.txt"

char toLower(char c);
char toUpper(char c);
char **readFile(char *filename, int *row, int *col);
char *toLowerString(char *str);
void printGrid(char **grid);
void searchWord(char **grid, char **updatedGrid, char *word, int row, int col);

int main() {
    int row, col;
    char **grid = readFile(FILENAME, &row, &col);
    char **updatedGrid = readFile(FILENAME, &row, &col);

    if (grid == NULL) {
        return 1;
    }
    char input[100];
    printf("Initial Grid\n");
    printGrid(grid);

    while (1){
        printf("Enter a word: ");
        scanf("%s", input);
        if (strcmp(input, "exit") == 0) {
            break;
        }
        searchWord(grid, updatedGrid, input, row, col);
    }
    return 0;
}

void searchWord(char **grid, char **updatedGrid, char *word, int row, int col) {
    int direction[8][2] = {
        {0, 1}, {1, 0}, {1, 1}, {1, -1},
        {0, -1}, {-1, 0}, {-1, -1}, {-1, 1}
    };
    int found = 0;
    int i, j, k;
    for (i = 0; grid[i] != NULL; i++) {
        for (j = 0; grid[i][j] != '\0'; j++) {
            // Search for 8 direction

            for (k = 0; k < 8; k++) {
                int x = i;
                int y = j;
                int l;
                for (l = 0; word[l] != '\0'; l++) {
                    if (x < 0 || x >= row || y < 0 || y >= col) {
                        break;
                    }
                    if (grid[x][y] != word[l]) {
                        break;
                    }
                    x += direction[k][0];
                    y += direction[k][1];
                }
                if (word[l] == '\0') {
                    found = 1;
                    x = i;
                    y = j;
                    for (l = 0; word[l] != '\0'; l++) {
                        updatedGrid[x][y] = toUpper(updatedGrid[x][y]);
                        x += direction[k][0];
                        y += direction[k][1];
                    }
                }
            }

        }
    }
    if (found) {
        printf("Word found\n");
    } else {
        printf("Word not found\n");
    }
    printGrid(updatedGrid);
}

void printGrid(char **grid) {
    int i;
    for (i = 0; grid[i] != NULL; i++) {
        printf("%s\n", grid[i]);
    }
}

char **readFile(char *filename, int *row, int *col) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File not found\n");
        return NULL;
    }

    fscanf(file, "%d %d ", row, col);

    char **lines = (char **)malloc(sizeof(char *) * (*row + 1));
    int i;
    for (i = 0; i < *row; i++) {
        lines[i] = (char *)malloc(sizeof(char) * (*col + 1));
        fscanf(file, "%s ", lines[i]);
        lines[i][*col] = '\0';
        lines[i] = toLowerString(lines[i]);
    }

    lines[*row] = NULL;
    fclose(file);

    return lines;
}

char *toLowerString(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = toLower(str[i]);
    }
    return str;
}

char toLower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

char toUpper(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}