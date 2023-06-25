#ifndef UTIL_H
# define UTIL_H

#include <stdio.h> // printf, scanf, fopen, fclose, fprintf, fscanf
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <limits.h>

# define MAX_WORD_SIZE 12 + 1 // max word size in program + 1 for '\0'
# define DICT "./dictionary.txt" // dictionary.txt path
# define IGNORE "./ignore.txt" // ignore.txt path
# define WORDS "./input.txt" // input.txt path
# define THRESHOLD 6 // threshold value
# define INPUT_MAX_WORD 300000 // max word number in input.txt
# define MAX_WORD_COUNT 100 // max word to enter

int			read_dict(const char *file_name, char dict[][MAX_WORD_SIZE]); // read dictionary.txt and fill the dict array
int			is_ignored_word(char word[]); // check if the word is in ignore.txt or not
int			is_ignored_letter(char ch); // check if the letter is in alphabet or not
int			read_text(const char *text_file, const char *ignore_file, char words[][MAX_WORD_SIZE]); // read input.txt and fill the words array
int			find_occurence(char words[][MAX_WORD_SIZE], char *str, int read_nbr); // find occurence of the word in the words array
int			find_line(char *str, char dict[][MAX_WORD_SIZE]); // find the line of the word in the dictionary.txt
int			find_closest(char *str, char dict[][MAX_WORD_SIZE]); // find the closest word in the dictionary.txt
double		dissimilarity(char *w1, char *w2, char dict[][MAX_WORD_SIZE], double threshold); // calculate the dissimilarity between two words
int			histogram(const char words[][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE + 5 + 20]); // create histogram and return the scale numbers
void		fill_inputs(char hist[][MAX_WORD_SIZE + 5 + 20], char *argv[], const int occurence[], char dict[][MAX_WORD_SIZE]); // fill the histogram array
double		distance_calc(double vector1[], double vector2[]);
void		print_args(int argc, char *argv[]);
// increase visibility
void		print_banner(void);
void		draw_line(void);
// external functions written from me
int			f_strcat(char *dest, char *src, int j);
int			f_atoi(const char *str, int len);
int			f_strlen(const char *str);
int			f_strcpy(char arr[MAX_WORD_SIZE], char str[]); // strcpy working with 2d array
// functions written from me to assign values to global variables
void		f_fill_informations_and_print_banner(int argc); // fill informations and print banner
void		f_get_info(char *file_name, int flag); // get informations from dictionary.txt

# endif
