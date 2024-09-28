#include <stdio.h>

#define SIZE 100
#define MAX 5
#define SENTINEL -1

void    insert_order(int arr[], int *n, int x);
void    get_max_n(const int arr[], int n, int x);
void    print_array(const double arr[], int n);
void    set_array(double arr[], int size);
void    update_array(double arr[], int size);


int main(){
    int n = 0;
    int arr[SIZE];
    int x;

    printf("******* PART 1 *******\n");
    while (1){
        printf("Enter a number: (enter %d for exit) " , SENTINEL);
        scanf("%d", &x);
        if (x == SENTINEL)
            break;
        insert_order(arr, &n, x);
        get_max_n(arr, n, MAX);
    }
    printf("******* PART 2 *******\n");
    double arr2[SIZE];
    printf("Enter the size of the array: (max 100) ");
    int size;
    scanf("%d", &size);
    if (size > SIZE || size < 0){
        printf("Invalid size\n");
        return 1;
    }
    set_array(arr2, size);
    update_array(arr2, size);
    print_array(arr2, size);
    return 0;
}


void    insert_order(int arr[], int *n, int x){
    int i;
    arr[*n] = x;
    *n = *n + 1;
    for (int i = 0; i < *n; i++){
        for (int j = 0; j < *n - i - 1; j++){
            if (arr[j] < arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void    get_max_n(const int arr[], int n, int x){
    if (n < x){
        for (int i = 0; i < n; i++){
            printf("%d ", arr[i]);
        }
    }
    else{
        for (int i = 0 ; i < x; i++){
            printf("%d ", arr[i]);
        }
    }
    printf("\n");
}


void print_array(const double arr[], int n){
    for (int i = 0; i < n; i++){
        printf("%.2lf ", arr[i]);
    }
    printf("\n");
}


void set_array(double arr[], int size){
    for (int i = 0; i < size; i++){
        printf("Enter a number: ");
        scanf("%lf", &arr[i]);
    }
}

void update_array(double arr[], int size){
    for (int i = 0; i < size; i++){
    if (i % 2 == 0)
        arr[i] = arr[i] / 2;
    else
        arr[i] = arr[i] * 2;
    }
}

