#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 1000
#define SIZE 12
#define PIVOT -5

int randomGenerator(int max);
void printArray(int arr[], int size);
int closest(int arr[], int index, int search);

int main() {
    int i;
    int search;
    int arr[SIZE + 1] = {PIVOT};
    srand(time(NULL));

    for (i = 0; i < SIZE; i++) {
        arr[i] = randomGenerator(MAX);
        arr[i + 1] = PIVOT;
    }

    printArray(arr, SIZE);

    printf("Enter a number to closest: ");
    scanf("%d", &search);

    printf("Closest number to %d is %d\n", search, closest(arr, 0, search));

    return 0;
}

int closest(int arr[], int index, int search) {
    if (arr[index] == PIVOT) {
        return arr[index - 1];
    }

    if (abs(arr[index] - search) < abs(closest(arr, index + 1, search) - search)) {
        return arr[index];
    } else {
        return closest(arr, index + 1, search);
    }
}

void printArray(int arr[], int size) {
    int i;
    printf("Array : {");
    for (i = 0; i < size; i++) {
        printf("%d", arr[i]);
        if (i + 1 != size) {
            printf(", ");
        }
    }
    printf("}\n");
}

int randomGenerator(int max) {
    return rand() % max;
}