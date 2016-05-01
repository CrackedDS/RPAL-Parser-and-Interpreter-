/*
 * stack.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#include "stack.h"

Stack::Stack() {
	size = 0;
	top = NULL;
}

Stack::~Stack() {
	while(top != NULL) {
		Node* pos;
		pos = top;
		top = top->prev;
		delete pos;
	}
}

Node* Stack::getTop() {
	return top;
}

Node* Stack::pop() {
	if(top == NULL)
		return NULL;
	Node* pos = top;
	top = top->prev;
	size--;
	return pos;
}

void Stack::push(Node* node) {
	node->prev = top;
	top = node;
	size++;
}

int Stack::getSize() {
	return size;
}

void Stack::righttotop(Node* child) {
	top->right = child;
}


