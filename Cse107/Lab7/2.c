
#include <stdio.h>
  
int select(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
  
        for (j = 0; j < n - i - 1; j++)
            if (arr[j] == arr[i] && i != j)
                return (printf("Output :True"));
    return (printf("Output :False"));
}
  
int main()
{
    int arr[] = { 5, 1, 4, 2, 8 };
    int n = sizeof(arr) / sizeof(arr[0]);
    select(arr, n);
    return 0;
}
