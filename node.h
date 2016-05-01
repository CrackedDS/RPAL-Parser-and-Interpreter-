/*
 * node.h
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#ifndef NODE_H_
#define NODE_H_

#include "token.h"

class Node {
public:
	Node();
	Token token;
	virtual ~Node();
	Node* left;
	Node* right;
	Node* prev;
};

#endif /* NODE_H_ */
