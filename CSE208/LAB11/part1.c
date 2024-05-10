#include <stdio.h>
#include <math.h>

typedef struct {
	double height;
	double width;
} Rectangle;

typedef struct {
	double side1;
	double side2;
	double side3;
} Triangle;

typedef struct {
	double radius;
} Circle;

void calculate_area(Rectangle rect, Triangle tri, Circle cir, double ares[]){
	ares[0] = rect.height * rect.width;
	ares[1] = tri.side1 * tri.side2 / 2.0;
	ares[2] = 3.14 * cir.radius * cir.radius;
}


int main(){
	Rectangle rect = {5.0, 3.0};
	Triangle tri = {3.0, 4.0, 5.0};
	Circle cir = {2.0};
	double ares[3];
	calculate_area(rect, tri, cir, ares);
	for (int i = 0; i < 3; i++)
		printf("%lf\n", ares[i]);
}
