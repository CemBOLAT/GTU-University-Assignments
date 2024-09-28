#include "util.h"

void    draw_line(void)
{
    printf("\033[34;1m======================\033[0m\n");
}

void    print_banner(void)
{
    printf("\033[32m");
    printf(">=>             >>       >=>>=> \n");
    printf(">=>            >>=>      >>   >=>                   >=>      >=>>=>\n");
    printf(">=>           >> >=>     >>    >=>                >=>  >=>      >=>\n");
    printf(">=>          >=>  >=>    >==>>=>   >====>       >=>     >=>   >=>\n");
    printf(">=>         >=====>>=>   >>    >=>              >=>      >=>     >=>\n");
    printf(">=>        >=>      >=>  >>     >>               >=>    >=>       >=>\n");
    printf(">=======> >=>        >=> >===>>=>                  >==>      >====>\n");
    printf("\033[0m");
    draw_line();
}
