#include "util.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

void	cb_free(void *data){
	if (data != NULL){
		free(data);
		data = NULL;
	}
}

void	cb_free2d(void **data){
	if (data != NULL){
		for (int i = 0; data[i] != NULL; i++){
			free(data[i]);
			data[i] = NULL;
		}
		free(data);
		data = NULL;
	}
}

int	cb_len2d(void **data){
	int i = 0;
	while (data[i] != NULL){
		i++;
	}
	return i;
}

int	cb_nbrOfWords(char *input, char *delim){
	int i = 0, nbrOFWords = 0;
	while (input[i] != '\0'){
		if (input[i] == *delim){
			while (input[i] == *delim){
				i++;
			}
			nbrOFWords++;
		}
		i++;
	}
	return nbrOFWords;
}

char	**splitInput(char *input, char *delim){
	int i = 0, nbrOFWords = 0;
	char **spInput = NULL;
	nbrOFWords = cb_nbrOfWords(input, delim);
	spInput = (char **)malloc(sizeof(char *) * (nbrOFWords + 2));
	spInput[nbrOFWords + 1] = NULL;
	char *token = strtok(input, delim);
	while (token != NULL){
		spInput[i] = (char *)malloc(strlen(token) + 1);
		strcpy(spInput[i], token);
		token = strtok(NULL, delim);
		i++;
	}
	return spInput;
}
