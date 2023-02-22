#include <stdio.h>

int fibonacci(int nbr)
{
    if (nbr == 2)
        return (1);
    else if (nbr == 0 || nbr == 1)
        return (nbr);
    else
        return (fibonacci(nbr - 2) + fibonacci(nbr - 1));
}

int main() 
{
    int nbr;
    int i;
    
    i = 0;
    printf("Lütfen kaç terim yazdırma istediğinizi girin: ");
    scanf("%d", &nbr);
    while (i < nbr)
    {
        printf("%d",fibonacci(i));
        i++;
        if (i != nbr)
            printf(", ");
    }
    return 0;
}
