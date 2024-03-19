#include "util.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

void	cb_free(void *data){
	if (data != NULL){
		free(data);
		data = NULL;
	}
}

void	cb_free2d(void **data){
	if (data || *data != NULL){
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
	return nbrOFWords + 1;
}

char	**splitInput(char *input, char *delim){
	int i = 0, nbrOFWords = 0;
	char **spInput = NULL;
	nbrOFWords = cb_nbrOfWords(input, delim);
	spInput = (char **)malloc(sizeof(char *) * (nbrOFWords + 1));
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

void	cb_drawLine(){
	printf("****************************************\n");
}

void	cb_toUpper(char *str)
{
	if (*str >= 'a' && *str <= 'z')
		*str -= 32;
}

char	*cb_trim(char *str)
{
	char *end;
	while (isspace(*str))
		str++;
	if (*str == 0)
		return str;
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end))
		end--;
	*(end + 1) = 0;
	return str;
}

bool	isValidGrade(char *grade)
{
	if (strcmp(grade, "AA") == 0)
		return true;
	if (strcmp(grade, "BA") == 0)
		return true;
	if (strcmp(grade, "BB") == 0)
		return true;
	if (strcmp(grade, "CB") == 0)
		return true;
	if (strcmp(grade, "CC") == 0)
		return true;
	if (strcmp(grade, "DC") == 0)
		return true;
	if (strcmp(grade, "DD") == 0)
		return true;
	if (strcmp(grade, "FD") == 0)
		return true;
	if (strcmp(grade, "FF") == 0)
		return true;
	return false;
}

char	*cb_capitalize(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32;
		i++;
	}
	return str;
}

char	*cb_itoa(int num)
{
	char *str = (char *)malloc(12);
	sprintf(str, "%d", num);
	return str;
}
