/*
 * node.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#include "node.h"

Node::Node() {
	left = NULL;
	right = NULL;
	prev = NULL;
}

Node::~Node() {
	if(right == NULL)
		delete right;
	if(left == NULL)
		delete left;
}
