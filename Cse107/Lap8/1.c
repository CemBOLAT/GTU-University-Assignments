
#include <stdio.h>

# define START 7
# define FINISH 20

int ft_ans(int start, int finish)
{
    if (start % 3 != 0)
        return (ft_ans(start + 1, finish));
    if (start <= finish)
    {
        printf ("%d",start);
        if (finish - start > 3)
            printf("+");
        return (start + ft_ans(start + 3,finish));
    }
    return (0);
}

int main()
{
    int tmp;
    
    tmp = (START) + (3 - (START % 3));
    if (tmp == START + 3)
        tmp -= 3;
    printf("=%d", ft_ans(tmp, FINISH));
}
