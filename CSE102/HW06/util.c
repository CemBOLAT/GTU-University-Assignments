#include "util.h"

void	print_output(int nbr[], int flag)
{
	int	i = 0;
	while (nbr[i] != 0){
		print_line(nbr[i], flag);
		i++;
	}
}

void print_output_multi(int	ans[], int size){
	int	i = 0;

	while (size > i){
		if (ans[i] != -1 && ans[i] != -2)
			print_line(ans[i], 1);
		i++;
	}
}

void	print_line(int i, int flag){
	FILE	*file;
	int		line_counter = 0;
	char	letter;
	if (flag == 1)
		file = fopen(PRODUCT, "r");
	else if (flag == 2)
		file = fopen(STOCK, "r");
	while (fscanf(file, "%c", &letter) != -1){
		if (letter == '\n') line_counter++;
		if (i == line_counter){
			while (fscanf(file, "%c", &letter) != -1 && letter != '\n') printf("%c", letter);
			printf("\n");
			fclose(file);
			return ;
		}
	}
}

int		f_strlen(const char *s1)
{
	int	i;

	i = 0;
	while (s1[i] != '\0'){
		i++;
	}
	return (i);
}


void	print_start_once(int	flag){
	char	letter;
	FILE	*file ;
	if (flag == 1){
		file = fopen(PRODUCT, "r");
			while (fscanf(file, "%c", &letter) != -1 && letter != '\n') printf("%c", letter);
			printf("\n");
	}
	else if (flag == 2){
		file = fopen(STOCK, "r");
		while (fscanf(file, "%c", &letter) != -1 && letter != '\n') printf("%c", letter);
		printf("\n");
	}
	fclose(file);
}

void draw_line(void)
{
	printf("\033[36m\n*******************************************************\033[0m\n");
}

/* printing homework banner to increase visibility */
void print_banner(void)
{
	draw_line();
	printf("\n\033[32m \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >======>     >=>   >=>\n \
	>=>    >=>   >=>    >=>   >> >=>   >>=> >=>       >=>        >=>   >=>    >=>   >=>    >=>   >=>  >=>                 >=>             >=>  \n \
	>=>    >=> >=>        >=> >=> >=> > >=> >=>       >=>   >>   >=> >=>        >=> >=>    >=>   >=> >=>                >=>  >=>        >=>\n \
	>=====>>=> >=>        >=> >=>  >=>  >=> >=====>   >=>  >=>   >=> >=>        >=> >> >==>      >>=>>       >====>   >=>     >=>      >=>     \n \
	>=>    >=> >=>        >=> >=>   >>  >=> >=>       >=> >> >=> >=> >=>        >=> >=>  >=>     >=>  >=>    >====>   >=>      >=>    >=> >=>\n \
	>=>    >=>   >=>     >=>  >=>       >=> >=>       >> >>    >===>   >=>     >=>  >=>    >=>   >=>   >=>             >=>    >=>    >=>    >=> \n \
	>=>    >=>     >===>      >=>       >=> >=======> >=>        >=>     >===>      >=>      >=> >=>     >=>             >==>          >=>>=>   \n \
	\t\t\t\t\t CEMAL BOLAT 210104004010 \033[0m\n\n");
}
