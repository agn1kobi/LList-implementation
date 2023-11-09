#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "llist.h"

#define SIZE 1024
typedef struct Student {
	int roll_no;
	int year;
	char *name;
	char *study;
}Student;

Node *head = NULL;

void print_student(void *data) {
	Student *student = (Student*)data;
	printf("roll number: %d,\nyear : %d,\nname: %s,\nstudy: %s,\n",student->roll_no,student->year,student->name,student->study);
}

int compare_data(void *a, void* b) {
	Student* studentA = (Student*)a;
	Student* studentB = (Student*)b;
	return studentA->roll_no - studentB->roll_no;
}

void store_student() {
	char buf[SIZE];
	char *endptr;
	errno = 0;
	Student* student = malloc(sizeof(Student));

	printf("Enter students rollNo\n");
	if(!fgets(buf,SIZE,stdin)) {
		printf("wtf did you do\n");
		return;
	}
	student->roll_no = strtol(buf,&endptr,10);
	memset(buf,0,SIZE);
	printf("Enter students year\n");
	if(!fgets(buf,SIZE,stdin)) {
		printf("wtf did you do\n");
		return;
	}
	student->year = strtol(buf,&endptr,10);
	memset(buf,0,SIZE);
	printf("Enter students name\n");
	if(fgets(buf,SIZE,stdin)) {
		buf[strcspn(buf, "\n")] = 0;
		student->name = malloc(strlen(buf) + 1);
		memcpy(student->name,buf,strlen(buf) + 1);
	}
	printf("Enter students study\n");
	memset(buf,0,SIZE);
	if(fgets(buf,SIZE,stdin)) {
		buf[strcspn(buf, "\n")] = 0;
		student->study = malloc(strlen(buf) + 1);
		memcpy(student->study,buf,strlen(buf) + 1);
	}
	
	insert_node(&head, student);
	sort_list(&head, compare_data);
	return;
}

void free_data(void* data) {
	Student* student = (Student*) data;
	free(student->name);
	free(student->study);
	free(student);
}

void delete_student() {
	char buf[SIZE];
	char *endptr;
	errno = 0;
	Student* student = malloc(sizeof(Student));

	printf("enter student's roll number\n");
	if(!fgets(buf,SIZE,stdin)) {
		printf("wtf did you do\n");
		return;
	}
	student->roll_no = strtol(buf,&endptr,10);
	delete_node(&head, student, compare_data, free_data);
	free(student);
	sort_list(&head, compare_data);
}

void lookup_student() {
	char buf[SIZE];
	char *endptr;
	errno = 0;
	Student* student = malloc(sizeof(Student));

	printf("Enter student's roll number\n");
	if(!fgets(buf, SIZE, stdin)) {
		printf("wtf did you do\n");
		return;
	}

	student->roll_no = strtol(buf,&endptr,10);

	Node* node = search_node(&head, student, compare_data);
	if(node == NULL) {
		printf("Student not found.\n");
	}
	else {
		print_student(node->data);
	}
	free(student);
}

int main(int argc, char **argv) {
	long a;
    	char buf[SIZE];
    	do
    	{
        	printf("Hi, What would you like to do today?\nLook up a student(1),\nEnter a student(2),\nDelete a student(3),\nList all students(4),\nExit program(0)\n");
		printf("=====================================================================\n");
        	if (!fgets(buf, SIZE, stdin))
        	{
			return 1;
		}
        	char *endptr;
        	errno = 0;
        	a = strtol(buf, &endptr, 10);
        	if (errno == ERANGE) {
            		printf("Sorry, this number is too small or too large.\n");
			continue;
        	}
        	else if (endptr == buf) {
                       	printf("did not read input, try again\n");
			continue;
		}
        	else if (*endptr && *endptr != '\n') {
                       printf("please only enter a number\n");
		       continue;
        	}
		switch (a) {
			case 1:	
				lookup_student();
				break;
			case 2:
				store_student();
				break;
			case 3:	
				delete_student();
				break;
			case 4:
				if(head == NULL)
					printf("List is empty.\n");
				else
					print_list(head, (void (*)(void *))print_student);
				break;
			case 0:
				printf("exiting\n");
				return 0;
		}

	} while (1);
}
