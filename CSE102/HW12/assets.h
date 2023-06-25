#ifndef ASSETS_H
#define ASSETS_H

typedef struct {
	char	type[20];
	int		ivals[1];
	double	svals[1];
} Asset1;

typedef struct {
	char	type[20];
	double	svals[2];
	int		ivals[2];
} Asset2;

typedef struct {
	char	type[20];
	char	string1[50];
	char	string2[50];
}Asset3;

typedef struct {
	char	type[20];
	double	value1;
	float	value2;
	double	value3;
}Asset4;

#endif
