#include "util.h"

int		dict_vector_nbr = 0;
int		dict_word_nbr = 0;
int		temp_argc;

int main(int argc, char *argv[]){
	char	words_arr[INPUT_MAX_WORD][MAX_WORD_SIZE], hist[argc][MAX_WORD_SIZE + 5 + 20];
	int		word_nbr, read_nbr;
	int		occurence_arr[argc - 1];
	f_fill_informations_and_print_banner(argc);
	char	dict[dict_word_nbr + 1][MAX_WORD_SIZE];
	if (argc < 2 || argc > MAX_WORD_COUNT) return (printf("Invalid number of arguments.\n >> Usage: %s <word1> <word2> <word3> ... <word100>\n", argv[0]), 0);
	word_nbr = read_text(WORDS, IGNORE, words_arr); // read text and store words in words array
	read_nbr = read_dict(DICT, dict); // read dictionary and store words in dict array
	if (read_nbr == -1 || word_nbr == -1) return (0); // if read_dict or read_text returns -1, exit
	if (argc == 2) { // argc 2 is for single word and special inputs
		occurence_arr[0] = find_occurence(words_arr, argv[1], word_nbr); // find occurence of argv[1] in words array
		if (occurence_arr[0] != -1) // if input is found in text
			return (printf("Enter word(s): %s\n\"%s\" appears in \"%s\" %d times.\n", argv[1], argv[1], WORDS, occurence_arr[0]), 0);
		else // if not try to find closest word in dictionary
		{
			int index = find_closest(argv[1], dict); // find closest word in dictionary
			if (index == -1) // if the input is not matched in dictionary
				return (printf("Enter word(s): %s\n\"%s\" is not matched in \"%s\"\n", argv[1], argv[1], WORDS), 0);
			occurence_arr[0] = find_occurence(words_arr,dict[index], word_nbr); // find occurence of closest word in text
			if (occurence_arr[0] != -1) // if closest word is found in text
				return (printf("Enter word(s): %s\n\"%s\" doesn't apeear in \"%s\" but \"%s\" appears %d times.\n",argv[1], argv[1], WORDS, dict[index], occurence_arr[0]), 0);
			else if (occurence_arr[0] == -1) // if closest word is not found in text
				return (printf("Enter word(s): %s\n\"%s\" is not matched in \"%s\"\n", argv[1], argv[1], WORDS), 0);
		}
	}
    else { // argc > 2 is for multiple words with a loop and histogram
        int scale = 1; // scale is used for scaling histogram
        printf("Enter word(s): ");
		print_args(temp_argc, argv); // print inputs
        printf("\n");
        for (int i = 0; i < argc - 1; i++){
            occurence_arr[i] = find_occurence(words_arr, argv[i + 1], word_nbr);
            if (occurence_arr[i] == -1){
                int index = find_closest(argv[i + 1], dict);
                if (index == -1){
                    occurence_arr[i] = INT_MAX;
                }
                else{
                    occurence_arr[i] = find_occurence(words_arr, dict[index], word_nbr);
                    if (occurence_arr[i] == -1)
                        occurence_arr[i] = INT_MAX;
                    else occurence_arr[i] = -occurence_arr[i];
                }
            }
        }
        fill_inputs(hist, argv, occurence_arr, dict); // fill histogram
        scale = histogram(words_arr, occurence_arr, hist); // find scale and print histogram
    }
    return (0);
}

// print arguments
void	print_args(int argc, char *argv[]){
	for (int i = 1; i < argc; i++) printf("%s ", argv[i]);
}


int find_closest(char *str, char dict[][MAX_WORD_SIZE]){

	double	min = -1, i = 0;
	char	answer[MAX_WORD_SIZE];
	int		return_value = 0;
	int		line;
	for (int k = 0; k < MAX_WORD_SIZE; k++) answer[k] = '\0';

	line = find_line(str, dict);
	if (line == -1) return (line);
	min = dissimilarity(dict[line], answer, dict, THRESHOLD);
	return_value = find_line(answer, dict);
	return (return_value);
}

void	fill_vectors(double vectors[][dict_vector_nbr]);

double dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold)
{
	int		i = 0, line;
	double	min = 0, vectors[dict_word_nbr][dict_vector_nbr], temp;
	double sum = INT_MAX;
	line = find_line(w1, dict);
	fill_vectors(vectors);
	while (i < dict_word_nbr){
		if (i != line){
			temp = distance_calc(vectors[line], vectors[i]);
			if(temp < sum)
			{
				sum = temp;
				min = (double)i;
			}
		}
		i++;
	}
	f_strcpy(w2, dict[(int)min]);
	return (min);
}

double	distance_calc(double vector1[], double vector2[]){
	double sum = 0, temp = 0;
	for (int i = 0; i < dict_vector_nbr; i++){
		temp = fabs(vector1[i] - vector2[i]);
		sum += temp * temp;
		if (sum > THRESHOLD * THRESHOLD) return (INT_MAX);
	}
	sum = sqrt(sum);
	return (sum);
}


void	fill_vectors(double vectors[][dict_vector_nbr]){
	FILE	*file = fopen(DICT, "r");
	int		i = 0;
	char	letter, str[MAX_WORD_SIZE];

	while (fscanf(file, "%c", &letter) != -1 && letter != '\n');
	while (i < dict_word_nbr){
		fscanf(file, "%s", str);
		for (int j = 0; j < dict_vector_nbr; j++)
			fscanf(file, "%lf", &vectors[i][j]);
		i++;
	}
	fclose(file);
}

int find_line(char *str, char dict[][MAX_WORD_SIZE])
{
	for (int i = 0; i < dict_word_nbr; i++)
		if (strcmp(str, dict[i]) == 0)
			return i;
	return -1;
}

int find_occurence(char words[][MAX_WORD_SIZE], char *str, int read_nbr)
{
	int count = 0;

	for (int i = 0; i < read_nbr; i++)
		if (strcmp(str, words[i]) == 0)
			count++;
	if (count == 0) return (-1);
	return (count);
}

int read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE])
{
	int i = 0;
	int count = 0;
	double tmp;
	FILE *file = fopen(text_file, "r");
	char str[MAX_WORD_SIZE], letter;
	while (fscanf(file, "%c", &letter) != -1)
	{
		if (letter != '\n' && letter != ' ')
		{
			if (is_ignored_letter(letter) == 1)
			{
				str[i] = letter;
				i++;
			}
		}
		else
		{
			str[i] = '\0';
			i = 0;
			if (is_ignored_word(str) == 1 && (str[0] != '\0'))
			{
				f_strcpy(words[count], str);
				count++;
			}
		}
	}
	words[count][0] = '-';
	words[count][1] = '\0';
	fclose(file);
	return (count);
}

int read_dict(const char *file_name, char dict[][MAX_WORD_SIZE])
{
	int i = 0, j = 0;;
	double tmp;
	FILE *fp = fopen(file_name, "r");
	char str[MAX_WORD_SIZE] , letter;
	fscanf(fp, "%c", &letter);
	while (letter != '\n') fscanf(fp, "%c", &letter);
	while (i < dict_word_nbr)
	{
		fscanf(fp, "%s", str);
		if (f_strcpy(dict[i], str) == -1)
		{
			fclose(fp);
			return (-1);
		}
		for (j = 0; j < dict_vector_nbr; j++) fscanf(fp, "%lf", &tmp);
		i++;
	}
	dict[i][0] = '-';
	dict[i][1] = '\0';
	fclose(fp);
	return (i);
}

int	is_ignored_word(char word[]){

	FILE *file = fopen(IGNORE, "r");
	char str[MAX_WORD_SIZE];


	while (fscanf(file, "%s", str) != -1)
		if (strcmp(word, str) == 0) return (fclose(file), 0);

	fclose(file);
	return (1);
}

int is_ignored_letter(char letter){
	if ((letter <= 'z' && letter >= 'a') || (letter <= 'Z' && letter >= 'A'))
		return (1);
	return (0);
}

void	f_fill_informations_and_print_banner(int argc){
	print_banner();
	f_get_info(DICT, 1);
	f_get_info(DICT, 2);
	temp_argc = argc;
	draw_line();
}

void f_get_info(char *file_name, int flag){
	FILE	*file = fopen(file_name, "r");
	char	str[50];
	int		res = 0, len = 0;

	for (int i = 0; i < flag; i++){
		fscanf(file, "%s", str);
	}
	len = f_strlen(str);
	res = f_atoi(str, len);
	if (flag == 1){
		dict_word_nbr = res;
	}
	else if (flag == 2){
		dict_vector_nbr = res;
	}
	fclose(file);
}

int		f_strcat(char *dest, char *src, int j){
	int i = 0;
	while (src[i] != '\0'){
		dest[j] = src[i];
		i++;
		j++;
	}
	return (j);
}

int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20]){
	int		scale = 1;
	int		max = 1;
	for (int i = 0; i < temp_argc - 1 ; i++){
		if ((abs(occurrences[i]) > max) && occurrences[i] != INT_MAX)
			max = abs(occurrences[i]);
	}
	if (max % 20 == 0) scale = max / 20;
	else scale = (max / 20) + 1;
	if (scale != 1) printf("Scale: %d\n", scale);
	for (int i = 0; i < temp_argc - 1; i++) {
		printf("%s", hist[i]);
		if (occurrences[i] < 0 && occurrences[i] != INT_MAX)
			for (int j = 0; j < abs(occurrences[i]) / scale ; j++) printf("+");
		else if (occurrences[i] != INT_MAX) for (int j = 0; j < abs(occurrences[i]) / scale; j++) printf("*");
		else if(occurrences[i] == INT_MAX) printf("NO MATCHES");
		printf("\n");
	}
	return (scale);
}


void    fill_inputs(char hist[][MAX_WORD_SIZE + 5 + 20], char *argv[], const int occurence[], char dict[][MAX_WORD_SIZE]){
	int i = 1;
	int j = 0;
	while (i < temp_argc){
		j = 1;
		hist[i - 1][0] = '"';
		while (argv[i][j - 1] != '\0'){
			hist[i - 1][j] = argv[i][j - 1];
			j++;
		}
		if (occurence[i - 1] > 0)
			hist[i - 1][j] = '"';
		else{
			hist[i - 1][j] = '-';
			j++;
			hist[i - 1][j] = '>';
			j++;
			int k = 0;
			j = f_strcat(hist[i - 1], dict[find_closest(argv[i], dict)], j);
			hist[i - 1][j] = '"';
		}
		j++;
		while (j < (MAX_WORD_SIZE + 20)){
			hist[i - 1][j] = ' ';
			j++;
		}
		hist[i - 1][j] = '\0';
		i++;
	}
	hist[i - 1][0] = '-';
	hist[i - 1][1] = '\0';
}

int	f_strlen(const char *str){
	int i = 0;
	while (str[i] != '\0') i++;
	return (i);
}

int f_atoi(const char *str, int len){
	int res = 0;
	while (str[len] != '=') len--;
	len++;
	while (str[len] != ',' && str[len] != '\0'){
		res = (res * 10) + (str[len] - '0');
		len++;
	}
	return (res);
}

int f_strcpy(char arr[MAX_WORD_SIZE], char str[]){
	int i = 0;
	if (!str) return (-1);
	while (str[i] != '\0'){
		arr[i] = str[i];
		i++;
	}
	arr[i] = '\0';
	return (1);
}

/* printing homework banner to increase visibility */
void	print_banner(void){
	printf("\n\033[32m\
		>=>    >=>                                                                    >=>\n\
		>=>    >=>                                                                    >=>                              >=>      >====>>=>\n\
		>=>    >=>    >=>     >===>>=>>==>    >==>    >=>      >=>    >=>     >> >==> >=>  >=>                       >=>  >=>        >=>\n\
		>=====>>=>  >=>  >=>   >=>  >>  >=> >>   >=>   >=>  >  >=>  >=>  >=>   >=>    >=> >=>        >====>        >=>     >=>      >=>\n\
		>=>    >=> >=>    >=>  >=>  >>  >=> >>===>>=>  >=> >>  >=> >=>    >=>  >=>    >=>=>          >====>        >=>      >=>    >=>\n\
		>=>    >=>  >=>  >=>   >=>  >>  >=> >>         >=>>  >=>=>  >=>  >=>   >=>    >=> >=>                       >=>    >=>     >=>\n\
		>=>    >=>    >=>     >==>  >>  >=>  >====>   >==>    >==>    >=>     >==>    >=>  >=>                        >==>         >=>\n\
	\t\t\t\t\t CEMAL BOLAT 210104004010 \033[0m\n\n");
}

/* printing line to increase visibility */
void	draw_line(void)
{
	printf("\033[36m\n*******************************************************\033[0m\n");
}
