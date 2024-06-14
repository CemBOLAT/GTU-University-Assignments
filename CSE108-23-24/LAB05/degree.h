#ifndef DEGREE_H

#define DEGREE_H

#include <stdio.h>

void	celsius_to_fah_cal(double celsius, double *fahrenheit, double *kelvin){
	*fahrenheit = celsius * 9 / 5 + 32;
	*kelvin = celsius + 273.15;
}

void	fahrenheit_to_cel_kel(double fahrenheit, double *celsius, double *kelvin){
	*celsius = (fahrenheit - 32) * 5 / 9;
	*kelvin = *celsius + 273.15;
}

void	kelvin_to_cel_fah(double kelvin, double *celsius, double *fahrenheit){
	*celsius = kelvin - 273.15;
	*fahrenheit = *celsius * 9 / 5 + 32;
}

void	print_temperatures(double celsius, double fahrenheit, double kelvin){
	printf("Celsius: %.2f\n", celsius);
	printf("Fahrenheit: %.2f\n", fahrenheit);
	printf("Kelvin: %.2f\n", kelvin);
}

#endif
