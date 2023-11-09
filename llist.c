#include <stdlib.h>
#include "llist.h"

Node* create_node(void* data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void insert_node(Node** head_ref, void* new_data) {
	Node* new_node = create_node(new_data);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

void delete_node(Node** head_ref, void* data, int (*cmp)(void *, void*), void (*free_data)(void*)){
	Node* temp = *head_ref, *prev;

	if(temp != NULL && (*cmp)(temp->data, data) == 0) {
		*head_ref = temp->next;
		(*free_data)(temp->data);
		free(temp);
		return;
	}
	while(temp != NULL && (*cmp)(temp->data,data) != 0) {
		prev = temp;
		temp = temp->next;
	}

	if(temp == NULL) return;
	
	prev->next = temp->next;
	(*free_data)(temp->data);
	free(temp);

}

Node* search_node(Node** head_ref, void* data, int (*cmp)(void*,void*)) {
	Node* current = *head_ref;
	
	while(current != NULL) {
		if((*cmp)(current->data, data) == 0) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

static void front_back_split(Node *source, Node** front_ref, Node** back_ref) {

	Node* fast;
	Node* slow;
	slow = source;
	fast = source->next;

	while(fast != NULL) {
		fast = fast->next;
		if(fast != NULL) {
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front_ref = source;
	*back_ref = slow->next;
	slow->next = NULL;
}

static Node* sorted_merge(Node *a, Node *b, int (*cmp)(void *, void *)) {
	Node* result = NULL;

	if(a == NULL)
		return (b);
	else if(b == NULL)
		return (a);

	if(cmp(a->data,b->data) <= 0) {
		result = a;
		result->next = sorted_merge(a->next, b, cmp);
	}
	else {
		result = b;
		result->next = sorted_merge(a, b->next, cmp);
	}
	return (result);
}


void sort_list(Node** head_ref, int(*cmp)(void *, void*)){
	Node* head = *head_ref;
	Node* a;
	Node* b;

	if(head == NULL || (head->next == NULL)) {
		return;
	}
	front_back_split(head, &a, &b);
	
	sort_list(&a, cmp);
	sort_list(&b, cmp);

	*head_ref = sorted_merge(a, b, cmp);
}

void print_list(Node *head_ref, void (*fptr)(void *data)) {
	while(head_ref != NULL) {
		(*fptr)(head_ref->data);
		head_ref = head_ref->next;
	}
}
