#include <stdio.h>

void fillArray(double arr[], int size){
	for(int i = 0; i < size; i++){
		printf("Give me a double to fill the array : ");
		scanf("%lf", &arr[i]);
	}
	printf("Your array is : ");
	for (int i = 0; i < size; i++){
		printf("arr[%d] = %.2lf ", i, arr[i]);
	}
	printf("\n");
}

int isPrime(double num){
	if(num < 2){
		return 0;
	}
	for(int i = 2; i < num; i++){
		if((int)num % i == 0){
			return 0;
		}
	}
	return 1;
}

int countPrimes(double arr[], int size){
	int count = 0;
	for(int i = 0; i < size; i++){
		if(isPrime(arr[i])){
			count++;
		}
	}
	return count;
}

void compareArrays(double arr1[], double arr2[], int result[], int size){
	for(int i = 0; i < size; i++){
		if(arr1[i] > arr2[i]){
			result[i] = 0;
		}else{
			result[i] = 1;
		}
	}
	printf("Comparison result : ");
	for(int i = 0; i < size; i++){
		printf("result[%d] = %d ", i, result[i]);
	}
	printf("\n");
}

int	searchQuery(char *query, char *target){
	int i = 0;
	int j = 0;
	int index = -1;
	while(query[i] != '\0'){
		j = 0;
		if (query[i] == target[j]){
			index = i;
			while(target[j] != '\0'){
				if(query[i] != target[j]){
					index = -1;
					break;
				}
				i++;
				j++;
			}
		}
		else
			i++;
	}
	return index;
}

int main(){
	int size;
	printf("Give me a int to sized your array ! : ");
	scanf("%d", &size);
	double arr[size];

	fillArray(arr, size);
	printf("Number of primes in the array is : %d\n", countPrimes(arr, size));


	double arr2[size];
	int		result[size];
	fillArray(arr2, size);
	compareArrays(arr, arr2, result, size);
	char	*query = "Hello World";
	char	*target = "World";
	printf("Index of the target string in the query string is : %d\n", searchQuery(query, target));
}
