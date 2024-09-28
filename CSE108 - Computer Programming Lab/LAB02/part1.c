#include "util.h"

int     volume_area_assigner(double *v, double *a, t_main *data, int i);
void    draw_line(void);

void    part1(t_main *data)
{
    double surface_area, volume;

    printf("\n\033[33;1mWrite a C program that calculates the surface area and volume of a user-defined geometric shape. \033[0m\n");
    printf("Enter the edge length for cude: ");
    scanf("%d", &data->cube.edge_length);
    while(data->cube.edge_length < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter the edge length for cude: ");
        scanf("%d", &data->cube.edge_length);
    }

    volume_area_assigner(&volume, &surface_area, data, 1);
    printf("Surface Area = %.2lf, Volume = %.2lf\n", surface_area, volume);
    draw_line();
    printf("Enter side length for rectangular prism: ");
    scanf("%d", &data->rectangular_prism.side_length);
    while(data->rectangular_prism.side_length < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter side length for rectangular prism: ");
        scanf("%d", &data->rectangular_prism.side_length);
    }

    printf("Enter side width: ");
    scanf("%d", &data->rectangular_prism.side_width);
    while(data->rectangular_prism.side_width < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter side width: ");
        scanf("%d", &data->rectangular_prism.side_width);
    }

    printf("Enter side height: ");
    scanf("%d", &data->rectangular_prism.side_height);
    while(data->rectangular_prism.side_height < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter side height: ");
        scanf("%d", &data->rectangular_prism.side_height);
    }
    volume_area_assigner(&volume, &surface_area, data, 2);
    printf("Surface Area = %.2lf, Volume = %.2lf\n", surface_area, volume);
    draw_line();

    printf("Enter the radius for sphere: ");
    scanf("%d", &data->sphere.radius);
    while(data->sphere.radius < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter the radius for sphere: ");
        scanf("%d", &data->sphere.radius);
    }
    volume_area_assigner(&volume, &surface_area, data, 3);
    printf("Surface Area = %.2lf, Volume = %.2lf\n", surface_area, volume);
    draw_line();
    printf("Enter the radius for cone: ");
    scanf("%d", &data->cone.radius);
    while(data->cone.radius < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter the radius for cone: ");
        scanf("%d", &data->cone.radius);
    }
    
    printf("Enter the height: ");
    scanf("%d", &data->cone.height);
    while(data->cone.height < 0)
    {
        printf("Invalid Input ! << a length cannot be negative >>\n");
        printf("Enter the height: ");
        scanf("%d", &data->cone.height);
    }
    volume_area_assigner(&volume, &surface_area, data, 4);
    printf("Surface Area = %.2lf, Volume = %.2lf", surface_area, volume);
}

int volume_area_assigner(double *v, double *a, t_main *data, int i)
{
    if (i == 1)
    {
        /*
            given formula --
            Surface area --> 6a^2
            Volume --> 6a^3
        */
        *v = pow(data->cube.edge_length, 3);
        *a = pow(data->cube.edge_length, 2) * 6;
    }
    else if (i == 2)
    {
        /*
            given formula --
            Surface area --> 2.(a.b + a.c + b.c);
            Volume --> a.b.c
        */
        *v = (data->rectangular_prism.side_height * data->rectangular_prism.side_length * data->rectangular_prism.side_width);
        *a = 2 * (  (data->rectangular_prism.side_height * data->rectangular_prism.side_length) + \
                    (data->rectangular_prism.side_height * data->rectangular_prism.side_width) + \
                    (data->rectangular_prism.side_width * data->rectangular_prism.side_length));
    }
    else if (i == 3)
    {
        /*
            given formula --
            Surface area --> 4 <pi> r^2
            Volume --> 4/3 . <pi>  r^3 
        */
        *v = (4 * (PI * pow(data->sphere.radius ,3))) / 3;
        *a = (4 * (PI * pow(data->sphere.radius ,2)));
    }
    else if (i == 4)
    {
        /*
            given formula --
            Surface area --> (<pi> * r) * (b + r)
            Volume --> 1/3 * <pi> * (r^2) *h
        */
        *v = (PI * pow(data->cone.radius, 2) * data->cone.height) / 3 ;
        *a = (PI * data->cone.radius) * (data->cone.radius + sqrt(pow(data->cone.radius, 2) + pow(data->cone.height, 2)));
    }
    return (1);
}

void    draw_line(void)
{
    printf("\033[34;1m======================\033[0m\n");
}