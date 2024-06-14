#include <stdio.h>

#define C 0
#define M 1
#define B 2

#define CAR_SPEED_MUX 20
#define ENGINE_POWER_DIVIDER 2
#define BIKE_SPEED 30

union VehicleData {
	struct {
		int door;
		int seat;
	}car;

	struct {
		int wheels;
		int power;
	} motorbike;

	struct {
		int wheels;
	} bicycle;

};

typedef struct s_vehicle {
	int type;
	union VehicleData data;
} Vehicle;


int calculateSpeed(Vehicle vehicle){
	int max_speed = 0;

	if (vehicle.type == C){
		max_speed = vehicle.data.car.door * CAR_SPEED_MUX;
	}
	else if (vehicle.type == M){
		max_speed = vehicle.data.motorbike.power / ENGINE_POWER_DIVIDER;
	}
	else if (vehicle.type == B){
		max_speed = BIKE_SPEED;
	}
	return max_speed;
}

void assignData(Vehicle *v, int type){
	v->type = type;
	if (type == C){
		v->data.car.door = 4;
		v->data.car.seat = 5;
	}
	else if (type == M){
		v->data.motorbike.wheels = 2;
		v->data.motorbike.power = 250;
	}
	else if (type == B){
		v->data.bicycle.wheels = 2;
	}
}

void modify_car_doors(Vehicle *v, int doors){
	if (v->type == C){
		v->data.car.door = doors;
	}
}

int main(){
	Vehicle car;
	Vehicle motorbike;
	Vehicle bicycle;
	assignData(&car, C);
	assignData(&motorbike, M);
	assignData(&bicycle, B);

	printf("Car Speed: %d\n", calculateSpeed(car));
	printf("Motorbike Speed: %d\n", calculateSpeed(motorbike));
	printf("Bicycle Speed: %d\n", calculateSpeed(bicycle));

	modify_car_doors(&car, 2);

	printf("Modified Car Speed: %d\n", calculateSpeed(car));
}
