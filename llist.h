#ifndef LLIST_H
#define LLIST_H

typedef struct Node {
	void* data;
	struct Node* next;
}Node;

Node* create_node(void* data);
void insert_node(Node** head_ref, void* data);
void delete_node(Node** head_ref, void* data,int (*cmp)(void*, void*), void (*free_data)(void*));
Node* search_node(Node** head_ref, void* data, int (*cmp)(void*, void*));
void sort_list(Node** head_ref, int(*cmp)(void *, void*));
void print_list(Node* head_ref, void (*fptr)(void *));


#endif
