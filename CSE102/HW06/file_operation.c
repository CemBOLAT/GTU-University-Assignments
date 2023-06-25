#include "util.h"


// adds product to end of the product file with users input
void	add_product(int *p_top,int *p_feature){

	FILE	*product = fopen(PRODUCT, "r+");
	char	type;
	char	brand[6], name[9];
	double	price;

	fseek(product, 0, SEEK_END);

	while (getchar() != '\n');
	printf("Enter a product: ");
	printf("<< Type(char) Name(string) Brand(string) Price(float) >>\n(Seperate with space)\n");
	printf(" >> ");
	scanf("%c %s %s %lf",&type, name, brand, &price);
	(*p_top) += 1;
	while (!(type == 'D' || type == 'O' || type == 'C' || type == 'F'))
	{

		while (getchar() != '\n');
		printf("INVALID INPUT \n<< type only can be 'D' 'O' 'C' or 'F' >>\n");
		printf("Enter a product: ");
		printf("<< Type(char) Name(string) Brand(string) Price(float) >>\n(Seperate with space)\n");
		printf(" >> ");
		scanf("%c %s %s %lf",&type, name, brand, &price);
	}
	fprintf(product, "%d,%c,%s,%s,%.1lf", (*p_top), type, name, brand, price);
	int	counter = 0;
	while (counter < (*p_feature) - 4) // 4 is the number of features that we have already added << type, name, brand, price >>
	{
		fprintf(product,",None"); // filling the rest of the features with None
		counter++;
	}
	fprintf(product, "\n"); // new line at the end of the product
	fclose(product);
}

// deletes product to end of the product file with users input
void	delete_product(int *p_top){

	FILE	*product = fopen(PRODUCT, "r+");
	FILE	*temp = fopen(TEMP, "w+"); // using temp.txt to store data from product.txt
	int		i_pID, line = 0, index = 1;
	char	letter;


	printf("Enter a pID: << 1-%d >>", *p_top);
	printf(" >> ");

	scanf("%d",&i_pID);
	while(getchar() != '\n');
	while (fscanf(product,"%c", &letter) != -1)
		fprintf(temp, "%c", letter);
	fclose(product);
	fseek(temp, 0, SEEK_SET); // puts cursor to the beginning of the file not to close and open again to read
	product = fopen(PRODUCT, "w+");
	usleep(10);
	while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
		fprintf(product,"%c", letter);
	fprintf(product,"\n");

	while (line < *p_top){ // scanning line by line
		if (line < i_pID - 1){ // exactly the same before the line that we want to delete
			while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
				fprintf(product,"%c", letter);
			fprintf(product,"%c", letter);
		}
		else if (line >= i_pID){ // exactly the same after the line that we want to delete
			while (fscanf(temp,"%c", &letter) != -1 && letter != ','); // ignoring first feature which is pID
			fprintf(product,"%d,", index - 1);
			while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
				fprintf(product,"%c", letter);
			fprintf(product,"%c", letter);
		}
		else{ // exactly the same after the line that we want to delete
			while (fscanf(temp,"%c", &letter) != -1 && letter != '\n');
			fscanf(temp,"%c", &letter);
		}
		index++;
		line++;
	}
	(*p_top) -= 1; // decreasing the number of products
	fclose(product);
	fclose(temp);
}

// updates product to end of the product file with users input
void	update_product(int *p_top, int *feature_nbr){

	FILE	*product = fopen(PRODUCT, "r+");
	FILE	*temp = fopen(TEMP, "w+");
	int		pID, i, feature, line = 0, feature_counter = 0;
	char	letter, feature_val[10];

	printf("Enter a pID: << 1-%d >>\n >> ", *p_top);
	scanf("%d",&pID);
	while(getchar() != '\n');
	while (fscanf(product,"%c", &letter) != -1 && letter != ',');
	printf("Enter a feature: << 1-%d >>\n", *feature_nbr);

	/*
		printing features
		for:	1-) Brand
				2-)	Type....
	*/
	for(i = 1; i <= *feature_nbr; i++){
		printf("%d-", i);
		while (fscanf(product,"%c", &letter) != -1 && letter != ',' && letter != '\n')
			printf("%c", letter);
		printf("\n");
	}
	printf(" >> ");
	scanf("%d", &feature);
	if (feature == 4){
		printf("Enter the price value :\n << for ex: 43.0 is correct way to declere 43 or 43.234 is not >>\n >> ");
	}
	else
		printf("Enter The Value of Feature:\n >> ");
	scanf("%s", feature_val);

	fseek(product, 0, SEEK_SET); // puts cursor to the beginning of the file not to close and open again to read
	while (fscanf(product,"%c", &letter) != -1) // copies the product file to temp file
		fprintf(temp, "%c", letter);
	fclose(product);
	fseek(temp, 0, SEEK_SET);
	product = fopen(PRODUCT, "w+"); // refleshes the product file to write
	usleep(10);
	while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
		fprintf(product, "%c", letter);
	fprintf(product, "%c", letter);
	while (line < pID - 1){ // copies the temp file to product file until the line that we want to update
		fscanf(temp,"%c", &letter);
		if (letter == '\n')
			line++;
		fprintf(product,"%c", letter);
	}
	while (fscanf(temp,"%c", &letter) != -1 && letter != '\n'){
		if (letter == ','){ // counts the features
			feature_counter++;
			fprintf(product,"%c", letter);
		}
		else if (feature == feature_counter){ // ignores the feature that we want to update then writes the new value
			if (*feature_nbr == feature_counter && pID != *p_top){
				fprintf(product, "%s\n%d,", feature_val, pID + 1); // the feature is the last feature and the product is not the last product
				line += 1;
			}
			else if (*feature_nbr == feature_counter && pID == *p_top)
				fprintf(product, "%s", feature_val);// the feature is the last feature and the product is the last product
			else
				fprintf(product,"%s,", feature_val);// other cases
			while (fscanf(temp,"%c", &letter) != -1 && letter != ','); // ignores the old value
			break;
		}
		else // product file and temp file are the same
			fprintf(product,"%c", letter);
	}
	line += 1;
	while (line <= *p_top){ // copies the temp file to product file until the end
		fscanf(temp,"%c", &letter);
		if (letter == '\n')
			line++;
		fprintf(product,"%c", letter);
	}
	fclose(product);
	fclose(temp);
}

void	add_feature(int *p_top, int *p_feature){

	FILE	*product = fopen(PRODUCT, "r+");
	FILE	*temp = fopen(TEMP, "w+");
	int		line = 0, location;
	char	feature_entry[10], letter;


	(*p_feature)++; // increasing the number of stock features
	printf("Enter a feature << max 10 letters >>\n >> ");
	scanf("%s", feature_entry);
	while (line <= (*p_top) && fscanf(product, "%c", &letter) != -1){
		if (letter != '\n')
			fprintf(temp, "%c", letter);
		else if (line == 0 && letter == '\n'){
			fprintf(temp, ",%s\n", feature_entry); // adding the new feature to the first line
			line++;
		}
		else if (line != 0 && letter == '\n') {
			fprintf(temp, ",None\n"); // filling the new feature with None
			line++;
		}
		usleep(5);
	}
	fseek(temp, 0, SEEK_SET);
	fseek(product, 0, SEEK_SET);
	while (fscanf(temp, "%c", &letter) != -1){ // copies the temp file to product file
		fprintf(product, "%c", letter);
	}
	fclose(product);
	fclose(temp);
}


// makinig exacly the same algoritm with add_product function
void	add_new_stock(int *s_top, int *s_feature){
	FILE	*stock = fopen(STOCK, "r+");
	char	branch[16];
	int		cur_stock, pID, counter = 0;


	fseek(stock, 0, SEEK_END);
	while (getchar() != '\n');
	printf("Enter a stock product: ");
	printf("<< pID(int) branch(string) stock(integer) >>\n(Seperate with space)\n");
	printf(" >> ");
	scanf("%d %s %d",&pID, branch, &cur_stock);
	(*s_top) += 1;
	fprintf(stock, "%d,%d,%s,%d", *s_top, pID, branch, cur_stock);
	while (counter < (*s_feature) - 4)
	{
		fprintf(stock,",None");
		counter++;
	}
	fprintf(stock, "\n");
	fclose(stock);
}

// makinig exacly the same algoritm with delete_product function
void	delete_stock(int *s_top, int *s_feature){
	FILE *stock = fopen(STOCK, "r+");
	FILE *temp = fopen(TEMP, "w+");
	int		i_pID, line = 0, pID, index = 1;
	char	letter;


	printf("Enter a sID: << 1-%d", *s_top);
	printf(" >> ");

	scanf("%d",&i_pID);
	while(getchar() != '\n');
	while (fscanf(stock,"%c", &letter) != -1)
		fprintf(temp, "%c", letter);
	fclose(stock);
    fseek(temp, 0, SEEK_SET);
	stock = fopen(STOCK, "w+");
	usleep(10);
	while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
		fprintf(stock,"%c", letter);
	fprintf(stock,"\n");

	while (line < *s_top){
		if (line < i_pID - 1){
			while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
				fprintf(stock,"%c", letter);
			fprintf(stock,"%c", letter);
		}
		else if (line >= i_pID){
			while (fscanf(temp,"%c", &letter) != -1 && letter != ',');

			fprintf(stock,"%d,", index - 1);
			while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
				fprintf(stock,"%c", letter);
			fprintf(stock,"%c", letter);
		}
		else{
			while (fscanf(temp,"%c", &letter) != -1 && letter != '\n');
			fscanf(temp,"%c", &letter);
		}
		index++;
		line++;
	}
	(*s_top) -= 1;
	fclose(stock);
	fclose(temp);
}

// makinig exacly the same algoritm with update_product function
void	update_stock(int *s_top, int *s_feature){

	FILE *stock = fopen(STOCK, "r+");
	FILE *temp = fopen(TEMP, "w+");
	int		pID, i, feature, line = 0, feature_counter = 0;
	char	letter, feature_val[10];

	printf("Enter a pID: << 1-%d >>\n >> ", *s_top);
	scanf("%d",&pID);
	while(getchar() != '\n');

	fseek(stock, 0, SEEK_SET);
	while (fscanf(stock,"%c", &letter) != -1 && letter != ',');
	printf("Enter a feature: << 1-%d >>\n", *s_feature);
	for(i = 1; i <= *s_feature; i++){
		printf("%d-", i);
		while (fscanf(stock,"%c", &letter) != -1 && letter != ',' && letter != '\n')
			printf("%c", letter);
		printf("\n");
	}
	printf(" >> ");
	scanf("%d", &feature);
	printf("Enter The Value of Feature: ");
	scanf("%s", feature_val);

	fseek(stock, 0, SEEK_SET);
	while (fscanf(stock,"%c", &letter) != -1)
		fprintf(temp, "%c", letter);
	fclose(stock);
	fseek(temp, 0, SEEK_SET);
	stock = fopen(STOCK, "w+");
	usleep(10);
	while (fscanf(temp,"%c", &letter) != -1 && letter != '\n')
		fprintf(stock, "%c", letter);
	fprintf(stock, "%c", letter);
	while (line < pID - 1){
		fscanf(temp,"%c", &letter);
		if (letter == '\n')
			line++;
		fprintf(stock,"%c", letter);
	}
	while (fscanf(temp,"%c", &letter) != -1 && letter != '\n'){
		if (letter == ','){
			feature_counter++;
			fprintf(stock,"%c", letter);
		}
		else if (feature == feature_counter){
			if (*s_feature == feature_counter && pID != *s_top){
				fprintf(stock, "%s\n%d,", feature_val, pID + 1);
				line += 1;
			}
			else if (*s_feature == feature_counter && pID == *s_top)
				fprintf(stock, "%s", feature_val);
			else
				fprintf(stock,"%s,", feature_val);
			while (fscanf(temp,"%c", &letter) != -1 && letter != ',');
			break;
		}
		else
			fprintf(stock,"%c", letter);
	}
	line += 1;
	while (line <= *s_top){
		fscanf(temp,"%c", &letter);
		if (letter == '\n')
			line++;
		fprintf(stock,"%c", letter);
	}
	fclose(stock);
	fclose(temp);
}
