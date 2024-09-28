#include "util.h"

int main()
{
	Customer	*head;
	int			input = 0;
	head = ll_init();

	while (input != 6)
	{
		print_menu();
		scanf(" %d", &input);
		switch (input)
		{
			case 1: head = insertCustomer(head); break;
			case 2: head = removeCustomer(head); break;
			case 3: displayCustomers(head); break;
			case 4: takeInputAndSearchCustomer(head); break;
			case 5: head = changePriority(head); break;
			case 6: printf("\nTerminating Program...\n"); break;
			default: printf("\nInvalid input!\n"); break;
		}
	}
	free_list(head);
	return (0);
}

void assign_priority(char *priority_name, int *level){
	if (strcmp(priority_name, "VIP")) *level = VIP;
	else if (strcmp(priority_name, "OD")) *level = OD;
	else if (strcmp(priority_name, "VETERAN")) *level = VETERAN;
	else if (strcmp(priority_name, "NORMAL")) *level = NORMAL;
	else {
		printf("Priority level error!\n");
		exit(1);
	}
}

void update_txt(Customer *head){
	FILE *fp = fopen(TXT, "w");
	Customer *tmp = head;
	fprintf(fp, "name,age,priority\n");
	while (tmp != NULL){
		fprintf(fp, "%s,%d,%s\n", tmp->name, tmp->age, tmp->priority);
		tmp = tmp->next;
	}
	fclose(fp);
}

Customer *ll_init(void)
{
	Customer *head = NULL, *next = NULL, *prev = NULL;
	char line[LINE_MAX];
	FILE *fp = fopen(TXT, "r");

	if (fp == NULL)
	{
		printf("File open failed!\n");
		exit(1);
	}
	fgets(line, LINE_MAX, fp);
	while (fgets(line, LINE_MAX, fp) != NULL)
	{
		int priority_level;
		char *name = (char *)malloc(sizeof(char) * LINE_MAX);
		int age;
		char *priority = (char *)malloc(sizeof(char) * LINE_MAX);
		sscanf(line, " %[^,],%d,%s", name, &age, priority);
		assign_priority(priority, &priority_level);
		if (head == NULL)
		{
			head = node_init(name, age, priority, priority_level);
			next = head;
		}
		else
		{
			next->next = node_init(name, age, priority, priority_level);
			next = next->next;
			if (prev == NULL)
				prev = head;
			else
				prev = prev->next;
		}
		free(name);
		free(priority);
	}
	fclose(fp);
	return (head);
}

Customer *node_init(char *name, int age, char *priority, int priority_level)
{
	Customer *newNode = (Customer *)malloc(sizeof(Customer));
	if (newNode == NULL)
	{
		printf("Malloc alocation failed!\n");
		exit(1);
	}
	newNode->name = strdup(name);
	newNode->age = age;
	newNode->priority = strdup(priority);
	newNode->priority_level = priority_level;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

void print_menu(void){
	printf("*********************************\n\n");
	printf("Welcome to the ABC BANK\n\n");
	printf("1-Insert a new customer\n");
	printf("2-Remove a customer\n");
	printf("3-Display customers in order\n");
	printf("4-Search a customer\n");
	printf("5-Change priority settings\n");
	printf("6-Exit\n\nPlease select an option: ");
}

void	free_list(Customer *head){
	Customer *tmp = head;
	while (tmp != NULL){
		head = head->next;
		free(tmp->name);
		free(tmp->priority);
		free(tmp);
		tmp = head;
	}
}
