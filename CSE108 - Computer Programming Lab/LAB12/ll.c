#include "util.h"

Customer *ll_insert(Customer *head, char *name, int age, char *priority, int level){
	Customer *new;
	Customer *tmp;

	new = node_init(name, age, priority, level);
	if (head == NULL)
	{
		head = new;
		return (head);
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;

	return (head);
}

Customer *insertCustomer(Customer *head)
{
	char *name = (char *)malloc(sizeof(char) * LINE_MAX);
	int age, priority_level;
	char *priority = (char *)malloc(sizeof(char) * LINE_MAX);
	do
	{
		printf("\nPlease enter Customer's name: ");
		scanf(" %[^\n]s", name);
		printf("Please enter Customer's age: ");
		scanf(" %d", &age);
		printf("Please enter Customer's Priority Group < case-sensitive >: ");
		scanf(" %[^\n]s", priority);
		assign_priority(priority, &priority_level);
	} while (priority_level != VIP && priority_level != OD && priority_level != VETERAN && priority_level != NORMAL);
	head = ll_insert(head, name, age, priority, priority_level);
	free(name);
	free(priority);
	printf("\nCustomer added successfully!\n");
	update_txt(head);
	return (head);
}

Customer *removeCustomer(Customer *head){
	char *name = (char *)malloc(sizeof(char) * LINE_MAX);
	Customer *tmp = head;
	Customer *prev = NULL;
	printf("Please enter Customer's name: ");
	scanf(" %[^\n]s", name);
	while (tmp != NULL){
		if (strcmp(tmp->name, name) == 0){
			if (prev == NULL){
				head = tmp->next;
				head->prev = NULL;
			}
			else if (tmp->next == NULL){
				tmp->prev->next = NULL;
			}
			else {
				prev->next = tmp->next;
				tmp->next->prev = prev;
			}
			free(tmp->name);
			free(tmp->priority);
			free(tmp);
			free(name);
			printf("\nCustomer removed successfully!\n");
			update_txt(head);
			return (head);
		}
		prev = tmp;
		tmp = tmp->next;
	}
	printf("Customer not found!\n");
	free(name);
	return (head);
}

void takeInputAndSearchCustomer(Customer *head)
{
	char *name = (char *)malloc(sizeof(char) * LINE_MAX);
	printf("Please enter Customer's name: ");
	scanf(" %[^\n]s", name);
	searchCustomer(head, name);
	free(name);
}

void searchCustomer(Customer *current, char *name)
{
	if (current == NULL)
	{
		printf("\nCustomer not found!\n");
		return;
	}
	if (strcmp(current->name, name) == 0)
	{
		printf("\nFound: %s - Age: %d - Priority: %s - Priority Level: %d\n", current->name, current->age, current->priority, current->priority_level);
		return;
	}
	searchCustomer(current->next, name);
}

void	displayCustomers(Customer *head){
	int 		i = 0;
	Customer	*tmp = head;

	for (int j = PIORITY_MAX; j >= 1; j--){
		tmp = head;
		while (tmp != NULL){
			if (tmp->priority_level == j){
				if (i == 0) printf("\nCustomers:\n");
				printf("%d. %s - Age: %d - Priority Group: %s - Priority Level : %d\n", i + 1, tmp->name, tmp->age, tmp->priority, tmp->priority_level);
				i++;
			}
			tmp = tmp->next;
		}
	}
}

Customer *changePriority(Customer *head){
	char *name = (char *)malloc(sizeof(char) * LINE_MAX);
	char *(priority[]) = {"NORMAL","VETERAN", "OD", "VIP"};
	int priority_level;
	Customer *tmp = head;
	printf("Please enter Customer's name: ");
	scanf(" %[^\n]s", name);
	while (tmp != NULL){
		if (strcmp(tmp->name, name) == 0){
			do {
				printf("Please enter new Priority Level : ");
				scanf("%d", &priority_level);
				if (priority_level != VIP && priority_level != OD && priority_level != VETERAN && priority_level != NORMAL)
					printf("Invalid Priority Level\n");
			} while (priority_level != VIP && priority_level != OD && priority_level != VETERAN && priority_level != NORMAL);
			tmp->priority_level = priority_level;
			free(tmp->priority);
			tmp->priority = strdup(priority[priority_level - 1]);
			printf("\nPriority level changed successfully!\n");
			printf("New Properties are following: \n");
			printf("%s - Age: %d - Priority: %s - Priority Level : %d\n", tmp->name, tmp->age, tmp->priority, tmp->priority_level);
			update_txt(head);
			free(name);
			return (head);
		}
		tmp = tmp->next;
	}
	printf("Customer not found!\n");
	free(name);
	return (head);
}
