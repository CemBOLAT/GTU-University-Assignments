#ifndef UTIL_H
# define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef PI
# define PI 3.14
#endif


struct cube{
    int edge_length;  
};

struct rectangular_prism
{
    int side_length;
    int side_width;
    int side_height;
};

struct sphere
{
    int radius;
};

struct  cone
{
    int radius;
    int height;
};

struct people
{
    int     weight;
    double  height;
};

typedef struct s_main
{
    struct cone cone;
    struct cube cube;
    struct sphere sphere;
    struct rectangular_prism rectangular_prism;
    struct people people;
} t_main;

void    part1(t_main *data);
void    part2(t_main *data);

#endif