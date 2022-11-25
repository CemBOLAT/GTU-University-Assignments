#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char    *portName = "/dev/ttyUSB0";
void    f_project_menu(void);
void    f_square_taken(int  nbr, FILE *ardunio);

int main(void)
{
    int i; // Selection --> what we wanna do with ardunio !
    int sqr;

    i = 0;
    while (1)
    {
        FILE *ardunio = fopen(portName, "w+");
        f_project_menu();
        scanf("%d", &i);
        printf("\n");
        if (i == 1)
        {
             printf("(1) TURN ON LED ON ARDUNIO\n");
            fprintf(ardunio,"%d",i);
        }
        else if (i == 2)
        {
            printf("(2) TURN OFF LED OFF ARDUNIO\n");
            fprintf(ardunio,"%d",i);
        }
        else if (i == 3)
        {
            printf("(3) FLASH ARDUINO LED 3 TIME\n");
            fprintf(ardunio,"%d",i);
        }
        else if (i == 4)
        {
            printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n");
            printf("\nENTER THEN NUMBER THAT YOU WANT TO TAKE THE SQUARE: ");
            scanf("%d",&sqr);
            fprintf(ardunio,"%d",i);
            f_square_taken(sqr,ardunio);
        }
        else if (i == 0)
            break;
        else
            printf("INVALID OPERATION\n");
        fclose(ardunio);
        sleep(1);
    }
    return (0);
}

void	f_project_menu(void)
{
	printf("\n## WELCOME TO GTU ARDUINO LAB\t\t##\n");
        printf("## STUDENT NAME: CEMAL BOLAT\t\t##\n");
        printf("## PLEASE SELECT FROM THE FOLLOWING\t##\n");
        printf("## MENU: \t\t\t\t##\n");
        printf("(1) TURN ON LED ON ARDUNIO\n");  
        printf("(2) TURN OFF LED ON ARDUNIO\n");
        printf("(3) FLASH ARDUINO LED 3 TIME\n");
        printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n");
        printf("(5) Button press counter (bonus item)\n");
        printf("(0) EXIT\n");
        printf("\nPLEASE SELECT: ");
}
void    f_square_taken(int  nbr, FILE *ardunio)
{
    int i = 4;
    int ans = 0;
    fflush(stdin);
    sleep(5);
    fprintf(ardunio,"%d",nbr);
    fscanf(ardunio,"%d",&ans);
    if (ans == 0 || ans != nbr * nbr)
    {
        freopen(portName,"w+",ardunio);
        fprintf(ardunio, "%d%d", i,nbr);
        sleep(2);
        fscanf(ardunio, "%d", &ans);
    }
    printf("THE SQUARE OF %d is %d\n", nbr, ans);
}
