/*
 * linked_list.h
 *
 *  Created on: 26 Oct 2013
 *      Author: leal
 */

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

#include <iostream>

template<typename Elem>
class Node {
public:
	Node(Elem e) {
		value = e;
		next = NULL;
	}
	virtual ~Node() {
	}
	;
	Elem value;
	Node *next;
};

template<class Elem>
class LinkedList {
public:

	LinkedList(Elem e) {
		Node<Elem> *n = new Node<Elem>(e);
		head = n;
	}
	LinkedList() {
		head = NULL;
	}

	void append(Elem e) {
		Node<Elem> *n = new Node<Elem>(e);

		if (head == NULL) {
			head = n;
		} else {
			Node<Elem> *tmp = head;
			head = n;
			n->next = tmp;

		}
	}
	void printContents() {
		Node<Elem> *pos = head;
		while (pos != NULL) {
			std::cout << pos->value << std::endl;
			pos = pos->next;

		}
	}

	Node<Elem> *search(Elem e) {

		if (head == NULL) {
			std::cerr << "List is empty." << std::endl;
			return NULL;
		} else {
			Node<Elem> *pos = head;
			while (pos != NULL && pos->value != e) {
				pos = pos->next;
			}
			return pos;
		}

	}

	virtual ~LinkedList() {
		Node<Elem> *pos = head;
		while (pos != NULL) {
			Node<Elem> *tmp = pos;
			delete tmp;
			pos = pos->next;
		}
		std::cout << "Linked list deleted..." << std::endl;
	}
	;

private:
	Node<Elem> *head;

};

#endif /* LINKED_LIST_H_ */
