#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int create_list(FILE *fp)
{
	struct list *head = NULL;

	char *buf=malloc(20*sizeof(char));

	while(!feof(fp))
	{
		if(fgets(buf, 20, fp))
		{
			if(same_element(&head, (voidptr)buf)== NULL)
			{
				if(list_to_add(&head, (voidptr)buf)== NULL)
				{
					printf("Error\n");
					return 0;
				}
			}
		}
	}
	free(buf);
	sort_list(&head);
	print(head);
	delete_list(&head);
	return 1;
}

struct list *list_to_add(struct list **head, voidptr *buf)
{
 	struct list *add;

	if((add = malloc(sizeof(struct list))) == NULL)
	{
		printf("Not enough memory\n");
		return NULL;
	}
	if((add->elem = malloc(strlen((buf)+1)*sizeof(buf))) == NULL)
	{
		printf("Not enough memory\n");
		return NULL;
	}

   	*strcpy(add->elem, buf);
	add->counter = 1;
  	add->next = (*head);
   	(*head) = add;

	return (*head);
}


struct list *same_element(struct list **head, voidptr *buf)
{
 	struct list *head_copy = *head;

	if(head_copy == NULL)
		return NULL;

	while(head_copy)
	{
		if(strcmp(head_copy->elem, buf) == 0)
		{
			(head_copy)->counter++;
			return (head_copy);
		}
		head_copy = head_copy->next;
	}
	return NULL;
}

void print(struct list *head)
{
	struct list *head_copy = head;

	while (head_copy)
	{
		printf("%d\t%s\n", head_copy->counter, (char*)(head_copy->elem));
		head_copy = head_copy->next;
	}
}

void delete_list(struct list **head)
{
	struct list* prev = NULL;

	while ((*head)->next)
	{
		free((*head)->elem);
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}

	free((*head)->elem);
	free(*head);
}

void split(struct list *src, struct list **low, struct list **high)
{
	struct list *fast = NULL;
	struct list *slow = NULL;
 
	if (src == NULL || src->next == NULL){
		(*low) = src;
		(*high) = NULL;
		return;
	}
 
	slow = src;
	fast = src->next;
 
	while (fast != NULL)
	{
		fast = fast->next;
		
		if (fast != NULL)
		{
			fast = fast->next;
			slow = slow->next;
 		}
	}
 
	(*low) = src;
	(*high) = slow->next;
	slow->next = NULL;
}

void merge(struct list *a, struct list *b, struct list **c)
{
	struct list tmp;
	*c = NULL;
	
	if(a == NULL)
	{
		*c = b;
		return;
	}

	if(b == NULL)
	{
		*c = a;
		return;
	}

	if(a->counter > b->counter)
	{
		*c = a;
		a = a->next;
	}
	else
	{
		*c = b;
		b = b->next;
	}

	tmp.next = *c;

	while(a && b)
	{

		if (a->counter > b->counter)
		{
			(*c)->next = a;
			a = a->next;
		}
		else
		{
			(*c)->next = b;
			b = b->next;
		}

		(*c) = (*c)->next;
	}

	if(a)
	{
		while(a)
		{
			(*c)->next = a;
			(*c) = (*c)->next;
			a = a->next;
		}
	}

	if(b)
	{
		while(b)
		{
			(*c)->next = b;
 			(*c) = (*c)->next;
			b = b->next;
		}
	}

	*c = tmp.next;
}

void sort_list(struct list **head)
{
	struct list *low  = NULL;
	struct list *high = NULL;

	if ((*head == NULL) || ((*head)->next == NULL))
	{
		return;
	}

	split(*head, &low, &high);
	sort_list(&low);
	sort_list(&high);
	merge(low, high, head);
}

