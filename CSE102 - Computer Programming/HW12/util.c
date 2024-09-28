#include "util.h"

void	print_data(void *data, int flag, int file){
	FILE *fp = NULL;

	if (file == 0){
		fp = fopen("serialized.txt", "a");
	}
	else{
		fp = fopen("deserialized.txt", "a");
	}
	if (!fp){
		f_exit("File open failed");
	}
	fprintf(fp,"***************\n");
	switch (flag){
		case 1:
			fprintf(fp, "type: %s\n", ((Asset1 *)data)->type);
			fprintf(fp, "ival: %d\n", ((Asset1 *)data)->ivals[0]);
			fprintf(fp, "sval: %lf\n", ((Asset1 *)data)->svals[0]);
			break;
		case 2:
			fprintf(fp, "type: %s\n", ((Asset2 *)data)->type);
			fprintf(fp, "ival1: %d\n", ((Asset2 *)data)->ivals[0]);
			fprintf(fp, "sval1: %lf\n", ((Asset2 *)data)->svals[0]);
			fprintf(fp, "ival2: %d\n", ((Asset2 *)data)->ivals[1]);
			fprintf(fp, "sval2: %lf\n", ((Asset2 *)data)->svals[1]);
			break;
		case 3:
			fprintf(fp, "type: %s\n", ((Asset3 *)data)->type);
			fprintf(fp, "string1: %s\n", ((Asset3 *)data)->string1);
			fprintf(fp, "string2: %s\n", ((Asset3 *)data)->string2);
			break;
		case 4:
			fprintf(fp, "type: %s\n", ((Asset4 *)data)->type);
			fprintf(fp, "value1: %lf\n", ((Asset4 *)data)->value1);
			fprintf(fp, "value2: %f\n", ((Asset4 *)data)->value2);
			fprintf(fp, "value3: %f\n", ((Asset4 *)data)->value3);
			break;
	}
	fclose(fp);
}
