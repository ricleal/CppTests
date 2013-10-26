/*
 * linked_list.cpp
 *
 *  Created on: 26 Oct 2013
 *      Author: leal
 */

#include "/home/leal/git/CppTests/linked_list.h"

int main_linkedlist(void) {

	LinkedList<int> l1 = LinkedList<int>(1);
	l1.append(2);
	l1.append(3);
	l1.printContents();
	Node<int> *f1 = l1.search(2);
	if (f1 != NULL)
		std::cout << "Found: " << f1->value << std::endl;

}

