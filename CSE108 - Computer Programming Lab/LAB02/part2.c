#include "util.h"


void    part2(t_main *data)
{
    double BMI;

    printf("\n\033[33;1mWrite a body mass index (BMI) calculator program. \033[0m\n");
    printf("Enter your weight(kg): ");
    scanf("%d", &data->people.weight);
    while(data->people.weight < 0)
    {
        printf("Invalid Input ! << a weight cannot be negative >>\n");
        printf("Enter your weight: ");
        scanf("%d", &data->people.weight);
    }
    printf("Enter your height(m): ");
    scanf("%lf", &data->people.height);
    while(data->people.weight < 0)
    {
        printf("Invalid Input ! << a height cannot be negative >>\n");
        printf("Enter your height(m): ");
        scanf("%lf", &data->people.height);
    }
    /*
        given formula = BMI = weight(kg) / height(m)^2 ; 
    */
    BMI = (double)data->people.weight / ((double)(pow((double)data->people.height, 2)));
    /*
            given conditions --
        •BMI less than 18.5:underweight
        •BMI between 18.5 and 24.9: average weight
        •BMI between 25 and 29.9: overweight
        •BMI of 30 or greater: obese
    */
    if (BMI < 18.5)
        printf("You are underweight <<< BMI : %.1lf >>>\n", BMI);
    else if (BMI >= 18.5 && BMI <= 24.9)
        printf("You are average weight <<< BMI : %.1lf >>>\n", BMI);
    else if (BMI >= 25 && BMI <= 29.9)
        printf("You are overweight <<< BMI : %.1lf >>>\n", BMI);
    else if (BMI >= 30)
        printf("You are obese <<< BMI : %.1lf >>>\n", BMI);
}