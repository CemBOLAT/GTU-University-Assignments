#include "degree.h"

void	print_menu(){
	printf("1. Celsius to Fahrenheit and Kelvin\n");
	printf("2. Fahrenheit to Celsius and Kelvin\n");
	printf("3. Kelvin to Celsius and Fahrenheit\n");
	printf("0. Exit\n");
}

int main(){

	do {
		print_menu();
		int choice;
		double celsius, fahrenheit, kelvin;

		printf("Choice: ");
		scanf("%d", &choice);

		switch(choice){
			case 1:
				printf("Type a temperature in Celsius: ");
				scanf("%lf", &celsius);
				celsius_to_fah_cal(celsius, &fahrenheit, &kelvin);
				print_temperatures(celsius, fahrenheit, kelvin);
				break;
			case 2:
				printf("Type a temperature in Fahrenheit: ");
				scanf("%lf", &fahrenheit);
				fahrenheit_to_cel_kel(fahrenheit, &celsius, &kelvin);
				print_temperatures(celsius, fahrenheit, kelvin);
				break;
			case 3:
				printf("Type a temperature in Kelvin: ");
				scanf("%lf", &kelvin);
				kelvin_to_cel_fah(kelvin, &celsius, &fahrenheit);
				print_temperatures(celsius, fahrenheit, kelvin);
				break;
			case 0:
				return 0;
				break;
			default:
				printf("Invalid choice\n");
				break;
		}
	} while(1);
}
