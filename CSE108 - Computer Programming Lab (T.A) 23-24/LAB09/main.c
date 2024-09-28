#include <stdio.h>
#include <string.h>

#define  MAX 100

int		isPalidrome(const char *str, int start, int end);
void	print_special_subs(const char *str, int start, int end);
void	hs(int a[], int *size, int max);

int main(){
	int a[MAX] = {3}, size = 1;

	hs(a, &size, MAX);
	for (int i = 0; i < size; i++)
		printf("%d ", a[i]);
	printf("\n");
	char *str = "abcddcba";
	if (isPalidrome(str, 0, strlen(str)-1))
		printf("Yes\n");
	else
		printf("No\n");
	print_special_subs(str, 0, strlen(str)-1);
}

int isPalidrome(const char *str, int start, int end){
	if (start >= end)
		return 1;
	if (str[start] != str[end])
		return 0;
	return isPalidrome(str, start+1, end-1);
}


// I want to print all the special sub strings of the given string
// being special is enought to same from start and end
void print_special_subs(const char *str, int start, int end){
	if (!(start < end)){
		start = 0;
		end--;
	}
	if (end <= 0)
		return;
	if (str[start] == str[end]){
		for (int i = start; i <= end; i++)
			printf("%c", str[i]);
		printf("\n");
	}
	print_special_subs(str, start+1, end);

}

void hs(int a[], int *size, int max){
	if (*size == max || a[*size - 1] == 1)
		return;
	if (a[*size - 1] % 2){
		a[*size] = 3 * a[*size - 1] + 1;
		(*size)++;
	}
	else{
		a[*size] = a[*size - 1] / 2;
		(*size)++;
	}
	hs(a, size, max);
}
