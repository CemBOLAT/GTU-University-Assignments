
#include <stdio.h>

int main()
{
    int n1, n2, tmp;
    printf("Lütfen modu alınacak sayıyı girin: ");
    scanf("%d", &n1);
    printf("Lütfen mod sayısını girin: ");
    scanf("%d", &n2);
    tmp = n1;
    while (n1 >= n2)
        n1 -= n2;
    printf("%d mod %d = %d\n",tmp, n2, n1);
}
