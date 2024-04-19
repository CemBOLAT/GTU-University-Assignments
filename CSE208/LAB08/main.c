#include <stdio.h>
#include <math.h>
#define NaN (0.0/0.0)

void most_three_freq(char *str){
	int freq[26] = {0};
	char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
					   'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
					   'u', 'v', 'w', 'x', 'y', 'z'};
	int i = 0;

	while(str[i] != '\0'){
		if(str[i] >= 'a' && str[i] <= 'z'){
			freq[str[i] - 'a']++;
		}
		i++;
	}
	for (int i = 0; i < 26; i++){
		for (int j = 0; j < 26; j++){
			if(freq[i] > freq[j]){
				int temp = freq[i];
				freq[i] = freq[j];
				freq[j] = temp;
				char temp2 = letters[i];
				letters[i] = letters[j];
				letters[j] = temp2;
			}
		}
	}
	for (int i = 0; i < 3; i++)
		printf("%c: %d\n", letters[i], freq[i]);
}

void file_reader(char *filename){
	FILE *file = fopen(filename, "r");
	float output[15][20];
	if(file == NULL){
		printf("File not found\n");
		return;
	}
	float num = 0;
	int numberOFNumbers[15] = {0};
	int i = 0, j = 0;
	while(fscanf(file, "%f", &num) != EOF){
		if (isnan(num))
			output[i][j] = 0.0;
		else
			output[i][j] = num;
		j++;
		char c = fgetc(file);
		if(c == '\n'){
			numberOFNumbers[i] = j;
			i++;
			j = 0;
		}
	}
	for (int k = 0; k < i; k++){
		for (int l = 0; l < numberOFNumbers[k]; l++){
			printf("%.2f ", output[k][l]);
		}
		printf("\n");
	}
	fclose(file);
}

int main(){
	char *str = "Hello World!";

	most_three_freq(str);
	file_reader("numbers.txt");
}
