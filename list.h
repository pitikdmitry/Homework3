#ifndef _LIST_H_
#define _LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* voidptr;

struct list{
	voidptr *elem;
	int counter;
	struct list *next;
};


struct list *list_to_add(struct list **head, voidptr *buf);
void print(struct list *head);
struct list *same_element(struct list **head, voidptr *buf);
void delete_list(struct list **head);
void sort_list(struct list **);
int create_list(FILE *fo);

#endif //_LIST_H
