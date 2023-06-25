#include "util.h"

int main()
{

    t_main *data;

    data = malloc(sizeof(t_main));
    if (!data)
        return (0);
    part1(data);
    part2(data);
    free(data);
    
}