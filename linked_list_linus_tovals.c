/*
 * linked_list_linus_tovals.c
 *
 *  Created on: 3 Nov 2013
 *      Author: leal
 *
 *  Comparing classic remove whit double pointer iteration (i.e. L. Tovalds).
 *
 *  Based on: http://grisha.org/blog/2013/04/02/linus-on-understanding-pointers/
 *
 *
 * At the opposite end of the spectrum, I actually wish more people understood the really core low-level kind of coding.
 * Not big, complex stuff like the lockless name lookup, but simply good use of pointers-to-pointers etc.
 * For example, I’ve seen too many people who delete a singly-linked list entry by keeping track of the “prev” entry,
 * and then to delete the entry, doing something like
 *
 * if (prev)
 *   prev->next = entry->next;
 * else
 *   list_head = entry->next;
 *
 * and whenever I see code like that, I just go “This person doesn’t understand pointers”. And it’s sadly quite common.
 *
 * People who understand pointers just use a “pointer to the entry pointer”, and initialize that with the address of the list_head.
 * And then as they traverse the list, they can remove the entry without using any conditionals,
 * by just doing a “*pp = entry->next”
 *
 */

#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */

typedef int bool;
#define true 1
#define false 0

typedef struct list_entry {
	int val;
	struct list_entry *next;
} list_entry;

void appendElem(list_entry ** head, list_entry *elem) {
	if (*head == NULL) {
		*head = elem;
		(*head)->next = NULL;
	} else {
		(elem)->next = (*head);
		*head = elem;
	}
}

void remove_classic(list_entry ** head, int to_remove) {
	list_entry *entry = *head; /* assuming head exists and is the first entry of the list */
	list_entry *prev = NULL;

	while (entry) {
		if (entry->val == to_remove) { /* this is the one to remove */
			if (prev)
				prev->next = entry->next; /* remove the entry */
			else
				*head = entry->next; /* special case - first entry */
		}
		/* move on to the next entry */
		prev = entry;
		entry = entry->next;
	}
}

void remove_tovalds(list_entry ** head, int to_remove) {
	list_entry **pp = head; /* pointer to a pointer */
	list_entry *entry = *head;

	while (entry) {
	    if (entry->val == to_remove)
	        *pp = entry->next;

	    pp = &entry->next;
	    entry = entry->next;
	}
}

int main_tovalds() {

	list_entry * head = NULL;

	list_entry *elem = (list_entry *) malloc(sizeof(list_entry));
	elem->val = 1;
	appendElem(&head, elem);
	elem = (list_entry *) malloc(sizeof(list_entry));
	elem->val = 2;
	appendElem(&head, elem);
	elem = (list_entry *) malloc(sizeof(list_entry));
	elem->val = 3;
	appendElem(&head, elem);

	for (elem = head; elem != NULL; elem = elem->next) {
		printf("-> %d\n", elem->val);
	}

	printf("Remove 2 classic: \n");
	remove_classic(&head, 2);

	for (elem = head; elem != NULL; elem = elem->next) {
		printf("-> %d\n", elem->val);
	}

	elem = (list_entry *) malloc(sizeof(list_entry));
	elem->val = 4;
	appendElem(&head, elem);

	for (elem = head; elem != NULL; elem = elem->next) {
		printf("-> %d\n", elem->val);
	}

	printf("Remove 3 Tovalds: \n");
	remove_tovalds(&head, 3);

	for (elem = head; elem != NULL; elem = elem->next) {
		printf("-> %d\n", elem->val);
	}


	return 0;

}
