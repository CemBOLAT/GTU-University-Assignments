#include <stdio.h>

#define LEN 5

int main()
{
    int i = 0;
    int j;
    while (i < LEN)
    {
        j = 0;
        while (j <= i)
        {
            printf("*");
            j++;
        }
        printf("\n");
        i++;
    }
}
