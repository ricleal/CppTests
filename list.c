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

void append(struct node* list, int i) {
	struct node* elem = (struct node *) malloc(sizeof(struct node));
	elem->value = i;
	struct node* pos = list;
	while (pos != NULL ) {
		pos = pos->next;
	}
	pos = elem;

}

int main_list() {
	printf("Main started.\n");
	struct node* list = NULL;
	append(list, 1);
	append(list, 2);
	append(list, 3);
	append(list, 4);

	struct node* pos = list;
	while (pos != NULL ) {
		printf("->%d\n",pos->value);
		pos = pos->next;
	}
	printf("Main finished.\n");
	return 0;
}
