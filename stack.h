/*
 * stack.h
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#ifndef STACK_H_
#define STACK_H_

#include "node.h"

class Stack {
private:
	int size;
	Node* top;
public:
	Stack();
	virtual ~Stack();
	Node* pop();
	void push(Node* node);
	int getSize();
	void righttotop(Node* child);
	Node* getTop();
};

#endif /* STACK_H_ */
