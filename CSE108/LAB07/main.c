# include <stdio.h>

void	f_draw_line(void);

int		part1(char	str[], int	len);
void	part2(void);
void	part3(void);

int		f_strlen(char	str[]);
void	foo_min_max(int arr[], int n);
void	f_draw_line(void);

int main(void)
{
	char	s[100];
	printf("Enter a string of lowercase letters: ");
	scanf("%s", s);
	part1(s, f_strlen(s));
	part2();
	part3();
}

//==========================================part1======================================

int	part1(char	str[], int	len)
{
	int i,j,temp, k = 0;
	int result = __INT_MAX__;
	while (k < 26) {
		temp = 1;
		i = 0;
		j = 0;
		while (str[j] != '\0' && str[i] != '\0')
		{
			while (str[j] == str[i] && str[j] != '\0') j++;
			if (str[i] != k + 'a') temp++;
			i = j;
		}
		if (temp < result) result = temp;
		k++;
	}
	printf("Minimum number of operation is: %d\n",result);
	return result;
}

//===========================================part 2=======================================

int check(char word[], char rule[], int i, int j)
{
	if (rule[j] == '\0') return 1;
	if (word[i] == '\0') return 0;
	if (word[i] == rule[j]) return check(word, rule, i + 1, j + 1);
	else if (rule[j] == '?') return check(word, rule, i + 1, j + 1);
	else if (rule[j] == '*') return check(word, rule, i + 1, j) || check(word, rule, i + 1, j + 1);
	else return check(word, rule, i + 1, j);
}

void part2()
{
	printf("Please enter the string and the rule respectively.\n >> ");
	char input[250];
	char rule[20];
	int i = 0, j = 0, k;
	scanf(" %[^\n]s", input);
	printf("Enter the rule: ");
	scanf("%s", rule);
	printf("Filtered text: ");
	while (input[i] != '\0')
	{
		char word[50];
		j = i;
		k = 0;
		while (input[j] != ' ' && input[j] != '\0') word[k++] = input[j++];
		word[k] = '\0';
		i = j;
		if (check(word, rule, 0, 0) == 0) printf("%s ", word);
		if (input[i] == ' ') i++;
	}
	printf("\n");
}

//==================================PART2==================================
//==================================PART3==================================

void	part3(void){
	int	size;
	printf("Enter the size: ");
	scanf("%d", &size);
	int	arr[size];
	for (int i = 0; i < size; i++){
		printf("%d. element of array: ", i + 1);
		scanf("%d", &arr[i]);
	}
	foo_min_max(arr, size);
}

void	foo_min_max(int arr[], int n)
{
	int max = arr[0];
	int min = arr[0];
	int i = 0;
	while (i < n)
	{
	if (arr[i] < min)
		min = arr[i];
	if (arr[i] > max)
		max = arr[i];
	i++;
	}
	printf("Min: %d Max: %d\n", min, max);
}



//==================================PART3==================================

 void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}

int	f_strlen(char	str[]){
	int	i = 0;
	while (str[i] != '\0'){
		i++;
	}
	return (i);
}
