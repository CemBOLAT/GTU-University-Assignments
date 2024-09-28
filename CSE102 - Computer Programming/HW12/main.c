#include "util.h"

int main(void)
{
	struct Node **head = (struct Node **)malloc(sizeof(struct Node *));

	srand(time(NULL));
	if (!head) {
		f_exit("Memory allocation failed\n");
	}
	*head = NULL;

	free_file();

	fillLinkedList(head);

	serializeLinkedList(*head);

	freeLinkedList(head);

	f_draw_line();
	printf("Serialized linked list to %s\n", BIN_FILE);

	head = (struct Node **)malloc(sizeof(struct Node *));
	if (!head) {
		f_exit("Memory allocation failed\n");
	}
	*head = NULL;

	deserializeLinkedList(head);

	freeLinkedList(head);

	f_draw_line();
	printf("Deserialized linked list from %s\n", BIN_FILE);
	f_draw_line();

	return 0;
}

/*
	Implement a function
	void serializeLinkedList(struct Node* head)
	that serializes the linked list and writes
	it to a binary file named linkedlist.bin.
*/

void serializeLinkedList(struct Node* head){ // serialize the linked list
	FILE *fp = fopen(BIN_FILE, "wb");

	Node *temp = head; // temp node to iterate through the linked list
	while (temp){
		void *data = temp->data; // void pointer to the data of the node
		if (strcmp(((Asset1 *)data)->type, "Asset1") == 0){
			print_data(data, 1, 0); // print the data of the asset to txt file to check if they are same after deserialization
			fwrite(data, sizeof(Asset1), 1, fp); // write the data to the binary file
		}
		else if (strcmp(((Asset2 *)data)->type, "Asset2") == 0){
			print_data(data, 2, 0);
			fwrite(data, sizeof(Asset2), 1, fp);
		}
		else if (strcmp(((Asset3 *)data)->type, "Asset3") == 0){
			print_data(data, 3, 0);
			fwrite(data, sizeof(Asset3), 1, fp);
		}
		else if (strcmp(((Asset4 *)data)->type, "Asset4") == 0){
			print_data(data, 4, 0);
			fwrite(data, sizeof(Asset4), 1, fp);
		}
		temp = temp->next;
	}
	fclose(fp);
}

/*
	Implement  a  function void  fillLinkedList(struct  Node**  head)that  generates  a  linked
	list  with  four different types of assetsand fills them with appropriate values.
*/

void	fillLinkedList(struct Node **head){
	int		numOfAssests = rand() % 11 + 10; // 10 ~ 20
	Node	*temp = NULL; // temp node to iterate through the linked list

	for (int i = 0; i < numOfAssests ; i++){
		Node	*newNode = (Node *)malloc(sizeof(Node)); // new node to add to the linked list
		newNode->next = NULL;
		int		assetsPick = rand() % 4 + 1; // 1 ~ 4
		if (!temp) { // if the linked list is empty
			*head = newNode;
			temp = *head;
		}
		else { // add node to the end of the linked list
			temp->next = newNode;
			temp = temp->next;
		}
		if (!newNode) f_exit("Memory Allocation failed\n");
		switch (assetsPick){
			case 1:
				Asset1 *asset1 = (Asset1 *)malloc(sizeof(Asset1)); // allocate memory for the asset
				strcpy(asset1->type, "Asset1"); // set the type of the asset
				asset1->ivals[0] = rand() % INT_MAX;
				asset1->svals[0] = rand();
				newNode->data = asset1; // set the data of the node to the asset
				break;
			case 2:
				Asset2 *asset2 = (Asset2 *)malloc(sizeof(Asset2));
				strcpy(asset2->type, "Asset2");
				asset2->ivals[0] = rand() % INT_MAX;
				asset2->svals[0] = rand();
				asset2->ivals[1] = rand() % INT_MAX;
				asset2->svals[1] = rand();
				newNode->data = asset2;
				break;
			case 3:
				Asset3 *asset3 = (Asset3 *)malloc(sizeof(Asset3));
				strcpy(asset3->type, "Asset3");
				for (int j = 0; j < 50; j++){
					asset3->string1[j] = rand() % 100 + 28;
					asset3->string2[j] = rand() % 100 + 28;
				}
				asset3->string1[49] = '\0';
				asset3->string2[49] = '\0';
				newNode->data = asset3;
				break;
			case 4:
				Asset4 *asset4 = (Asset4 *)malloc(sizeof(Asset4));
				strcpy(asset4->type, "Asset4");
				asset4->value1 = rand();
				asset4->value2 = rand();
				asset4->value3 = rand();
				newNode->data = asset4;
				break;
		}
	}
}

void deserializeLinkedList(struct Node **head)
{
	FILE *fp = fopen(BIN_FILE, "rb");
	Node *temp = NULL;

	if (!fp) {
		f_exit("File open failed\n");
	}

	while (1)
	{
		char type[20];

		int flag = fread(type, sizeof(char), sizeof(type), fp);
		if (flag != sizeof(type)) {
			break;
		}
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->next = NULL;
		if (!newNode) {
			f_exit("Memory allocation failed\n");
		}
		if (!(*head)) {
			*head = newNode;
			temp = *head;
		}
		else {
			temp->next = newNode;
			temp = temp->next;
		}
		if (strcmp(type, "Asset1") == 0) {
			fseek(fp, -sizeof(type), SEEK_CUR);
			Asset1 *asset = (Asset1 *)malloc(sizeof(Asset1));
			if (!asset){
				f_exit("Memory allocation failed\n");
			}
			fread(asset, sizeof(Asset1), 1, fp);
			newNode->data = asset;
			print_data(asset, 1, 1);
		}
		else if (strcmp(type, "Asset2") == 0) {
			fseek(fp, -sizeof(type), SEEK_CUR);
			Asset2 *asset = (Asset2 *)malloc(sizeof(Asset2));
			if (!asset) {
				f_exit("Memory allocation failed\n");
			}
			fread(asset, sizeof(Asset2), 1, fp);
			newNode->data = asset;
			print_data(asset, 2, 1);
		}
		else if (strcmp(type, "Asset3") == 0) {
			fseek(fp, -sizeof(type), SEEK_CUR);
			Asset3 *asset = (Asset3 *)malloc(sizeof(Asset3));
			if (!asset) {
				f_exit("Memory allocation failed\n");
			}
			fread(asset, sizeof(Asset3), 1, fp);
			newNode->data = asset;
			print_data(asset, 3, 1);
		}
		else if (strcmp(type, "Asset4") == 0) {
			fseek(fp, -sizeof(type), SEEK_CUR);
			Asset4 *asset = (Asset4 *)malloc(sizeof(Asset4));
			if (!asset) {
				f_exit("Memory allocation failed\n");
			}
			fread(asset, sizeof(Asset4), 1, fp);
			newNode->data = asset;
			print_data(asset, 4, 1);
		}
	}
	fclose(fp);
}

void freeLinkedList(struct Node **head)
{
	struct Node *temp = *head;
	struct Node *prev = NULL;

	while (temp) {
		prev = temp;
		temp = temp->next;
		free(prev->data);
		free(prev);
	}
	free(head);
}

void	free_file(){
	FILE *fp = fopen("./serialized.txt", "w+");
	fclose(fp);
	fp = fopen("./deserialized.txt", "w+");
	fclose(fp);
}

void f_draw_line()
{
	printf("\033[34m***************************************\n\033[0m");
}

void	f_exit(char *str){
	printf("%s\n", str);
	exit(0);
}
