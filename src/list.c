/*
 * list
 *
 *  Created on: 26 Oct 2013
 *      Author: leal
 *
 *
 *
 *  Few tests with C
 *  Nothing is working!
 *
 */

#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

struct node {
	int value;
	struct node *next;
};

void append(struct node** list, int i) {
	//struct node *start = &(*list);
	struct node *start = list;

	printf ("*list=%x list=%x &list=%x *start=%x start=%x &start=%x\n", *list,list,&list,*start,start,&start);
	struct node* elem = (struct node *) malloc(sizeof(struct node));
	elem->value = i;
	if (*list == NULL) { //first!
		//printf("List is null.\n");
		*list = elem;
		//printf("Was! List : %d\n", (*list)->value);
	} else {
		struct node** pos = list;
		while (*pos != NULL) {
			*pos = (*pos)->next;
		}
		*pos = elem;
	}
	list = &(*start);
	//printf ("start = %x ; list = %x\n",start,list);
}

int main_list() {
	printf("Main started.\n");
	struct node* list = NULL;
	append(&list, 1);
	printf("List : %d\n", list->value);

	append(&list, 2);
	printf("List : %d\n", list->value);

	append(&list, 3);
	append(&list, 4);

	printf("List : %d\n", list->value);

	struct node* pos = list;
	while (pos != NULL) {
		printf("->%d\n", pos->value);
		pos = pos->next;
	}
	printf("Main finished.\n");
	return 0;
}
