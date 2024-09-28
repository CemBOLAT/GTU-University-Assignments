#include <stdio.h>

#define LEN 5

int main()
{
    int i = 0;
    int s = LEN - 1;
    int j;
    int y = 1;
    while (i < LEN)
    {
        j = 0;
        while (j < s)
        {
            printf(" ");
            j++;
        }
        s--;
        j = 0;
        while (j < y)
        {
            printf("*");
            j++;
        }
        y += 2;
        printf("\n");
        i++;
    }
}
