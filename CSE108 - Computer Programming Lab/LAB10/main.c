#include "util.h"

int main()
{
	int		*part1, min_value;
	int		*part2_arr1, *part2_arr2;
	int		size_arr;
	Student	*part3 = NULL;
	float	average_gpa = 0, overall_avg_gpa = 0;

	srand(time(NULL));
	f_draw_line();
	printf("Welcome to LAB09 - Cemal BOLAT\n"); // welcome message
	printf("Enter the size of the array : "); // get the size of the array part1
	scanf("%d", &size_arr); // get the size of the array part1
	if (size_arr <= 0) { // check the size of the array part1
		printf("Error: Invalid size ! \n");
	}
	else {
		part1 = init_arr(size_arr); // allocate memory for the array part1
		f_draw_line();
		printf("Enter the elements of the array : "); // get the elements of the array part1
		for (int i = 0; i < size_arr; i++){
			scanf("%d", &part1[i]);
		}
		min_value = part1[0]; // I used selection
		for (int i = 1; i < size_arr; i++) {
			if (part1[i] < min_value)
				min_value = part1[i];
		}
		printf("Min of the array elements : %d\n", min_value); // print the min value of the array part1
		free_arr(part1);
	}
	f_draw_line();
	printf("Enter the elements of integers : ");
	scanf("%d", &size_arr);
	if (size_arr <= 0){
		printf("Error: Invalid size ! \n");
	}
	else {
		part2_arr1 = init_arr(size_arr); // allocate memory for the array part2
		part2_arr2 = calloc(size_arr, sizeof(int)); // allocate memory for the array part2 (calloc usage)
		printf("Enter %d integers : ", size_arr);
		for (int i = 0; i < size_arr; i++)
		{
			scanf("%d", &part2_arr1[i]);
		}
		part2_arr2[0] = part2_arr1[0]; // I used cumulative sum
		for (int i = 1; i < size_arr; i++)
		{
			part2_arr2[i] += part2_arr2[i - 1] + part2_arr1[i];
		}
		printf("First array: ");
		print_array(part2_arr1, size_arr);
		printf("Second array (cumulative sum) : ");
		print_array(part2_arr2, size_arr);
		free_arr(part2_arr1);
		free_arr(part2_arr2);
	}
	f_draw_line();
	for (int i = 0; i < STUDENT_NUM ; i++){
		average_gpa += init_student_struct(part3);
	}
	overall_avg_gpa = average_gpa / STUDENT_NUM;
	printf("Average GPA of %d x %d students: %.5f\n", STUDENT_NUM, STUDENT_NUM, overall_avg_gpa);
	f_draw_line();
}

void print_array(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

float init_student_struct(Student *arr)
{
	int i = 0;
	float average_gpa = 0;

	arr = (Student *)malloc(sizeof(Student) * STUDENT_NUM);
	if (!arr)
	{
		printf("Error: Memory allocation failed!\n");
		usleep(10); // wait 10 microseconds to print the error message
		exit(1); // terminate the process
	}

	for (int i = 0; i < STUDENT_NUM; i++)
	{
		arr[i].ID = i + 1;
		arr[i].age = (rand() % 18) + 10;
		arr[i].gpa = (float)(rand() % 401) / 100;
		average_gpa += arr[i].gpa;
	}
	free(arr);
	return (average_gpa / STUDENT_NUM);
}

int *init_arr(int size){
	int *arr = (int *)malloc(sizeof(int) * size);
	return (arr);
}

void free_arr(int *arr){
	free(arr);
}

void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}
