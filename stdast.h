/*
 * stdast.h
 *
 *  Created on: Apr 22, 2016
 *      Author: deepa
 */

#ifndef STDAST_H_
#define STDAST_H_

#include "node.h"
#include "rdp.h"

class StdAst {
private:
	RDP parser;
	Token tokengamma;
	Token tokenlambda;
	Node* stdLet(Node* node);
//	Node* stdTau(Node* node);
//	void stdTauHelper(Node* aug, Node* temp);
	Node* stdWhere(Node* node);
//	Node* stdArrow(Node* node);
//	Node* stdNot(Node* node);
	Node* stdWithin(Node* node);
//	Node* stdNeg(Node* node);
	Node* stdRec(Node* node);
	Node* stdFcn(Node* node);
//	void stdFcnHelper(Node* tempv);
	Node* stdLambda(Node* node);
//	Node* stdOp(Node* node);
	Node* stdAnd(Node* node);
	Node* stdAt(Node* node);
//	Node* stdUop(Node* node);
public:
	StdAst();
	~StdAst();
	Node* stdBegin(Node* node);
};


#endif /* STDAST_H_ */
