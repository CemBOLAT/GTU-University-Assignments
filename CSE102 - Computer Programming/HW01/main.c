#include "util.h"

// I blocked negative numbers in task 1, 2 and 3 because our teacher said !!
/*
	Firstly I named my files names as part1.c part2.c ...
	But teacher warned us to combine all of them in a util.c.
*/

/* I used struct to reduce variables and store them in one*/

int main(void)
{
	struct s_main *data;

	// I used malloc to apply changes
	data = (struct s_main *)malloc(sizeof(struct s_main));
	// Malloc control because it may not opened
	if (!data)
		return (0);

	/*		--> HOMEWORK 01 BANNER */
	/*	printing colorful texts to shell has four major parts.
		\033[		--> It corresponds to the ESC character.
		32			--> Color code < green >
		m			--> apply graphical mode <constant>
		\033[0m		--> reset the graphical mode
		<<<   ignore the whitespaces   >>>
		\033[	32	m	<<text>>  \033[0m
	*/
	printf("\033[32m\n>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >======>     >=>   >=> \n");
	printf(">=>    >=>   >=>    >=>   >> >=>   >>=> >=>       >=>        >=>   >=>    >=>   >=>    >=>   >=>  >=>              >=>      >=> \n");
	printf(">=>    >=> >=>        >=> >=> >=> > >=> >=>       >=>   >>   >=> >=>        >=> >=>    >=>   >=> >=>             >=>  >=>    >=> \n");
	printf(">=====>>=> >=>        >=> >=>  >=>  >=> >=====>   >=>  >=>   >=> >=>        >=> >> >==>      >>=>>             >=>     >=>   >=> \n");
	printf(">=>    >=> >=>        >=> >=>   >>  >=> >=>       >=> >> >=> >=> >=>        >=> >=>  >=>     >=>  >=>          >=>      >=>  >=> \n");
	printf(">=>    >=>   >=>     >=>  >=>       >=> >=>       >> >>    >===>   >=>     >=>  >=>    >=>   >=>   >=>          >=>    >=>   >=> \n");
	printf(">=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >=>      >=> >=>     >=>          >==>      >===> \n\t\t\t\t\tCEMAL BOLAT 210104004010\n\n\033[0m");

	part1(data);
	part2(data);
	part3(data);
	part4(data);

	// I freed where I malloced.
	free(data);
	return (0);
}
