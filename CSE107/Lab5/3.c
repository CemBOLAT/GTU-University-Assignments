#include <stdio.h>
#include <math.h>

int main()
{
    int res = 0;
    int x, n;
    int i = 1;
    
    printf("Lütfen x değerini girin: ");
    scanf("%d", &x);
    printf("Lütfen n değerini girin: ");
    scanf("%d", &n);
    while (i <= n)
    {
        res += i * (pow(x,i));
        i++;
    }
    res += 5;
    printf("f(%d) = %d\n", x,res);
}
