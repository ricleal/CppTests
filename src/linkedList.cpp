/*
 * linkedList.cpp
 *
 *  Created on: May 22, 2013
 *      Author: leal
 */

#include<iostream>

template<typename T>
class List {
public:
	List() {
		head = NULL;
	}
	void cleanup() {
		std::cout << "Cleaning List..." << std::endl;
		Node<T> * currentPtr = head;
		Node<T> * toDelete;
		while (currentPtr != NULL) {
			toDelete = currentPtr;
			currentPtr = currentPtr->next;
			delete (toDelete);
		}
		std::cout << "List cleaned..." << std::endl;
	}
	void insert(T value) {
		Node<T> *elem = new Node<T>(value);
		if (head == NULL)
			head = elem;
		else {
			Node<T>* lastElem = head;
			while (lastElem->next) {
				lastElem = lastElem->next;
			}
			lastElem->next = elem;
		}
	}

	void deleteElem(int pos) {
		if (pos < 0 || head == NULL)
			return;
		int currentPos = 0;
		Node<T> * currentPtr = head;
		Node<T> * temp;

		if (pos == 0){
			head = head->next;
			delete(currentPtr);
			return;
		}

		while (currentPtr != NULL) {
			if (pos == currentPos){
				temp->next = currentPtr->next;
				delete(currentPtr);
				return;
			}
			temp = currentPtr;
			currentPtr = currentPtr->next;
			currentPos ++;

		}
		std::cout << "List cleaned..." << std::endl;

	}

	bool isEmpty() {
		return head == NULL ? true : false;
	}
	void print() {
		if (isEmpty()) {
			std::cout << "List is empty" << std::endl;
		} else {
			Node<T> * currentPtr = head;
			std::cout << "List : " << std::endl;
			while (currentPtr != NULL) {
				std::cout << currentPtr->data << ' ';
				currentPtr = currentPtr->next;
			}
			std::cout << std::endl;
		}
	}

private:
	template<typename T1>
	class Node {
	public:
		Node() {
			next = NULL;
		}
		Node(T1 t) {
			data = t;
			next = NULL;
		}
		T1 data;
		Node* next;
	};
private:
	Node<T>* head;
};

int main_linkedList() {
	std::cout << "Main: START" << std::endl;

	List<int> l;
	l.insert(1);
	l.insert(2);
	l.insert(3);
	l.print();

	l.deleteElem(1);
	l.print();

	l.deleteElem(0);
	l.print();

	l.cleanup();
	std::cout << "Main: END" << std::endl;
}
