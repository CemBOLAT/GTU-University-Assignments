#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char    portName[] = "/dev/ttyUSB3";
void    f_project_menu(void);
void    f_ardunio_listener(int command);
void    f_square_taken(int  nbr, FILE *ardunio);
void    f_button_counter(FILE *ardunio);

int main(void)
{
    int i; // Selection --> what we wanna do with ardunio !

    i = 0;
    while (1)
    {
        f_project_menu();
        printf("\nPLEASE SELECT: ");
        scanf("%d", &i);
        printf("\n");
        if (i >= 1 && i <= 5)
            f_ardunio_listener(i);
        else if (i == 0)
            return (0);
        else
            printf("INVALID OPERATION !! TRY AGAIN !!\n");
    }
    f_ardunio_listener(2);
    return (0);
}

void f_project_menu()
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
    return ;
}

void    f_ardunio_listener(int  command)
{
    FILE *ardunio;
    int sqr;
    ardunio = fopen(portName,"w+");
    switch (command)
    {
    case 1:
        printf("(1) TURN ON LED ON ARDUNIO\n");
        fprintf(ardunio,"%d",command);
        break;
    case 2:
        printf("(2) TURN OFF LED ON ARDUNIO\n");
        fprintf(ardunio,"%d",command);
        break;
    case 3:
        printf("(3) FLASH ARDUINO LED 3 TIME\n");
        fprintf(ardunio,"%d",command);
        break;
    case 4:
        printf("(4) SEND A NUMBER TO ARDUINO TO COMPUTE SQUARE BY ARDUINO\n");
        printf("\nENTER THEN NUMBER THAT YOU WANT TO TAKE THE SQUARE: ");
        scanf("%d",&sqr);
        fprintf(ardunio,"%d",command);
        f_square_taken(sqr,ardunio);
        break;
    case 5:
        printf("(5) Button press counter (bonus item)\n");
        f_button_counter(ardunio);
        break;
    }
    freopen(portName,"w+",ardunio);
    fclose(ardunio);
}

void    f_square_taken(int  nbr, FILE *ardunio)
{
    fflush(stdin);
    int a = 4;
    int temp = 0;
    fprintf(ardunio,"%d",nbr);
    fscanf(ardunio,"%d", &temp);
    if (temp == 0 || temp != nbr * nbr)
    {
        freopen(portName,"w+",ardunio);
        fprintf(ardunio, "%d", a);
        fprintf(ardunio, "%d", nbr);
        sleep(15);
        fscanf(ardunio, "%d", &temp);
    }
    printf("THE SQUARE OF %d is %d\n", nbr, temp);
}

void f_button_counter(FILE *ardunio)
{
    fflush(stdin);
    int b = 5;
    int times;
    int temp;
    freopen(portName,"w+",ardunio);
    fscanf(ardunio, "%d", &temp);
    printf("LET ME KNOW THE PRESSING LIMIT !");
    scanf("%d", &times);
    while (1)
    {
        fprintf(ardunio, "%d", b);
        int a = 0;
        fscanf(ardunio, "%d", &a);
        if (a != 0)
        {
            printf("%d\n", a);
        }
    freopen(portName,"w+",ardunio);
    if (a == times)
        break; 
    }
    printf("YOU PUSHED TO THE BUTTON %d times\n",times);
}