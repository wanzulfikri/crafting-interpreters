#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct Node {
	char* data;
	struct Node* next;
	struct Node* prev;
};

void push(struct Node** head, char * data) {
	struct Node* new_node = malloc(sizeof(struct Node));
	new_node->data = data;
	if((*head) == NULL) {
		(*head) = new_node;
	} else {
		struct Node* current = *head;
		while(current->next != NULL) {
			current = current->next;
		}
		current->next = new_node;
		current->next->prev = current;
	}
}

void pop(struct Node** head) {
	struct Node* actual_head = *head;
	if((actual_head) == NULL) {
		printf("Nothing to pop...\n");
	} else if (actual_head->next == NULL) {
		actual_head = NULL;
	} else {
		while(actual_head->next != NULL) {
			actual_head = actual_head->next;
		}
		actual_head = actual_head->prev;
		free(actual_head->next);
		actual_head->next = NULL;
	}
}

int find(struct Node* head, char * strToSearch) {
	int found = 0;
	int count = 0;
	while(head != NULL) {
		if(!strcmp(head->data, strToSearch)) {
			found = 1;
			printf("Found %s", strToSearch);
			break;
		}
		head = head->next;
		count++;
	}
	if (!found) {
		printf("Not found %s\n", strToSearch);
		return -1;
	}
	return count;
}
int length(struct Node* head) {
	int count = 0;
	while(head != NULL) {
		count++;
		head = head->next;
	}
	return count;
}
void insert(struct Node** head, int index, char * data) {
	struct Node* current = *head;
	int list_length = length(current);
	if(!list_length) {
		printf("Nothing to insert\n");
	} if(index > list_length - 1) {
		printf("Index is larger than list length\n");
	} else {
		struct Node* new_node = malloc(sizeof(struct Node));
		new_node->data = data;
		if(index == 0) {
			*head = new_node;	
		} else {
			int count = 0;
			while(count != index) {
				current = current->next;
				count++;
			}
			new_node->next = current;
			new_node->prev = current->prev;
			current->prev->next = new_node;
			current->prev = new_node;
		}

	}
}



char* readString() {
	fflush(stdin);
	char *input = malloc((MAX + 1) * sizeof(char));
	printf("Enter: ");
	fgets(input, MAX, stdin);
	printf("---\n");
	return input;
}

void readAndPush(struct Node** node) {
	char *input = readString();
	push(node, input);
}

void list(struct Node* head) {
	if(head == NULL) {
		printf("It's empty.\n");
	} else {
		while(head != NULL){
			printf("%s", head->data);
			head = head->next;
		}
	}
	
	printf("---\n");
}

void delete(struct Node** head, int index) {
	struct Node* current = *head;
	int list_length = length(current);
	if(!list_length) {
		printf("Nothing to delete\n");
	} if(index > list_length - 1) {
		printf("Index is larger than list length\n");
	} else {
 		if(index == 0) {
			*head = current->next;
			free(current);
 		}  else {
 			int count = 0;
 			while(count != index) {
 				current = current->next;
 				count++;
 			}
 			
			current = current->prev;
 			if(list_length == index) {
 				free(current->next);
 				current->next = NULL;
 			} else {
 				current->next = current->next->next;
 				free(current->next->prev);
 				current->next->prev = current;
 
 			}
 		}

	}

}

int main(){
	struct Node* node = NULL; 
	push(&node, "test\n");
	push(&node, "momokoa\n");
	push(&node, "momo\n"); 
	// list(node);
	pop(&node);
	// list(node);
	printf("Length: %d\n", length(node));
	// find(node, "test\n");
	// find(node, "mo\n");
	insert(&node, 2, "bottom insert\n");
	insert(&node, 1, "bottom insert\n");
	list(node);
	delete(&node, 1);
	list(node);
	delete(&node,0);
	list(node);
	delete(&node,0);
	list(node);

}
