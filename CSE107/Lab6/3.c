#include <stdio.h>

# define MAX_NBR 10

int main()
{
    int nbr = 3;
    int pivot ;

    while (MAX_NBR - nbr >= 0)
    {
        pivot = 2 ;
        while (pivot < nbr)
        {
            if (nbr % pivot == 0)
            {
                printf("%d is composite\n", nbr);
                break ;
            }
            pivot++;
        }
        nbr++;
    }
    return (0);
}
