/*
 * stdast.cpp
 *
 *  Created on: Apr 22, 2016
 *      Author: deepa
 */

#include "stdast.h"
#include "stack.h"
#include <queue>
#include <cstdlib>

using namespace std;

StdAst::StdAst() {
	tokengamma = Token("gamma", "gamma");
	tokenlambda = Token("lambda", "lambda");
}

StdAst::~StdAst() {

}

Node* StdAst::stdBegin(Node* root) {
	Node* topRoot = root;
	Node* nextChild = topRoot->left;
	bool firstChild = true;
	while(nextChild != NULL){
		Node* transformedChild = stdBegin(nextChild);
		if(firstChild == true){
			topRoot->left = transformedChild;
			topRoot = topRoot->left;
			firstChild = false;
		}else{
			topRoot->right = transformedChild;
			topRoot = topRoot->right;
		}
		nextChild = nextChild->right;
	}
	Token rootToken = root->token;
	if(rootToken.value=="let"){
		root = stdLet(root);
	}else if(rootToken.value =="where"){
		root = stdWhere(root);
	}else if(rootToken.value == "function_form"){
		root = stdFcn(root);
	}else if(rootToken.value == "within"){
		root = stdWithin(root);
	}else if(rootToken.value == "and"){
		root = stdAnd(root);
	}else if(rootToken.value == "@"){
		root = stdAt(root);
	}else if(rootToken.value == "lambda"){
		root = stdLambda(root);
	}else if(rootToken.value == "rec"){
		root = stdRec(root);
	}

	return root;
}

Node* StdAst::stdLet(Node* node) {
	if(node->left->token.value != "=")
		exit(1);
	Node* gamma = new Node;
	gamma->token = tokengamma;
	Node* lambda = new Node;
	lambda->token = tokenlambda;

	gamma->left = lambda;
	lambda->right = node->left->left->right;
	lambda->left = node->left->left;
	lambda->left->right = node->left->right;

	return gamma;
}

/* only for full standardization
Node* StdAst::stdTau(Node* node) {
	Node* gamma1 = new Node;
	gamma1->token = tokengamma;
	Node* gamma2 = new Node;
	gamma2->token = tokengamma;
	Node* aug = new Node;
	aug->token = Token("aug", "aug");

	Node* temp = node->left;
	gamma1->left = gamma2;
	gamma2->right = temp;
	gamma2->left = aug;
	stdTauHelper(aug, temp);

	delete node;
	return gamma1;
}

void StdAst::stdTauHelper(Node* aug, Node* temp) {
	if(temp->right != NULL) {
		Node* gamma1temp = new Node;
		gamma1temp->token = tokengamma;
		Node* gamma2temp = new Node;
		gamma2temp->token = tokengamma;
		Node* augtemp = new Node;
		augtemp->token = Token("aug", "aug");

		aug->right = gamma1temp;
		gamma1temp->left = gamma2temp;
		gamma2temp->right = temp->right;
		gamma2temp->left = augtemp;
		stdTauHelper(augtemp, temp->right);
		temp->right = NULL;
	} else
		aug->right = NULL;
}
*/

Node* StdAst::stdWhere(Node* node) {
	if(node->right->token.value != "=")
		exit(1);
	Node* gamma = new Node;
	gamma->token = tokengamma;
	Node* lambda = new Node;
	lambda->token = tokenlambda;

	gamma->left = lambda;
	lambda->right = node->left->right->left->right;
	lambda->left = node->left->right->left;
	lambda->left->right = node->left;

	return gamma;
}

/* only for full standardization
Node* StdAst::stdArrow(Node* node) {
	Node* gamma1 = new Node;
	gamma1->token = tokengamma;
	Node* gamma2 = new Node;
	gamma2->token = tokengamma;
	Node* gamma3 = new Node;
	gamma3->token = tokengamma;
	Node* gamma4 = new Node;
	gamma4->token = tokengamma;
	Node* lambda1 = new Node;
	lambda1->token = tokenlambda;
	Node* lambda2 = new Node;
	lambda2->token = tokenlambda;
	Node* cond = new Node;
	cond->token = Token("Cond", "Cond");
	Node* braces1 = new Node;
	braces1->token = Token("()", "()");
	Node* braces2 = new Node;
	braces2->token = Token("()", "()");

	gamma1->left = gamma2;
	gamma2->right = NULL;
	gamma2->left = gamma3;
	gamma3->right = lambda1;
	lambda1->left = braces1;
	braces1->right = node->left->right->right;
	node->left->right->right = NULL;
	gamma3->left = gamma4;
	gamma4->right = lambda2;
	lambda2->left = braces2;
	braces2->right = node->left->right;
	node->left->right = NULL;
	gamma4->left = cond;
	cond->right = node->left;

	delete node;
	return gamma1;
}

Node* StdAst::stdNot(Node* node) {
	Node* gamma = new Node;
	gamma->token = tokengamma;

	gamma->left = node;
	node->right = node->left;
	node->left = NULL;

	return gamma;
}
*/

Node* StdAst::stdWithin(Node* node) {
	Node* gamma = new Node;
	gamma->token = tokengamma;
	Node* lambda = new Node;
	lambda->token = tokenlambda;
	Node* equal = new Node;
	equal->token = Token("=", "=");

	equal->left = node->left->right->left;
	Node* tempe2 = node->left->right->left->right;
	equal->left->right = gamma;
	gamma->left = lambda;
	lambda->right = node->left->left->right;
	lambda->left = node->left->left;
	lambda->left->right = tempe2;

	return equal;
}

/* only for full standardization
Node* StdAst::stdNeg(Node* node) {
	Node* gamma = new Node;
	gamma->token = tokengamma;

	gamma->left = node;
	node->right = node->left;
	node->left = NULL;

	return gamma;
}
*/

Node* StdAst::stdRec(Node* node) {
	Node* gamma = new Node;
	gamma->token = tokengamma;
	Node* lambda = new Node;
	lambda->token = tokenlambda;
	Node* equal = new Node;
	equal->token = Token("=", "=");
	Node* ystar = new Node;
	ystar->token = Token("YSTAR","YSTAR");

	Node* e = node->left->left->right;
	Node* x1 = node->left->left;
	x1->right = NULL;
	Node* x2 = new Node;
	x2->token = x1->token;
	equal->left = x1;
	x1->right = gamma;
	gamma->left = ystar;
	ystar->right= lambda;
	lambda->left = x2;
	x2->right = e;

	return equal;
}

Node* StdAst::stdFcn(Node* node) {
/*	Node* equal = new Node;
	equal->token = Token("=", "=");
	Node* lambda = new Node;
	lambda->token = tokenlambda;

	equal->left = node->left;
	Node* tempv = node->left->right;
	equal->left->right = lambda;
	lambda->left = tempv;
	stdFcnHelper(tempv);

	delete node;
	return equal;
*/
	Node* equal = new Node;
	equal->token = Token("=", "=");
	int count = 0;
	Stack stack;
	stack.push(node->left);
	Node* child = node->left->right;
	while(child != NULL){
		count++;
		stack.push(child);
		child = child->right;
	}
	count = count - 1;
	while(count != 0){
		Node* first = stack.pop();
		Node* second = stack.pop();
		second->right = first;
		Node* lambda = new Node;
		lambda->token = tokenlambda;
		lambda->left = second;
		stack.push(lambda);
		count--;
	}
	Node* first = stack.pop();
	Node* second = stack.pop();
	second->right = first;
	equal->left = second;

	return equal;
}

/*
void StdAst::stdFcnHelper(Node* tempv) {
	if(tempv->right->right != NULL) {
		Node* lambda = new Node;
		lambda->token = tokenlambda;

		Node* tempv1 = tempv->right;
		tempv->right = lambda;
		lambda->left = tempv1;
		stdFcnHelper(tempv1);
	}
}
*/

Node* StdAst::stdLambda(Node* node) {
	if(node->left->right->right == NULL)
		return node;
	Stack stack;
	Node* child = node->left;
	while(child != NULL){
		stack.push(child);
		Node* next = child->right;
		child->right = NULL;
		child = next;
	}
	while(stack.getSize() != 1){
		Node* rightChild = stack.pop();
		Node* leftChild = stack.pop();
		Node* lambda = new Node;
		lambda->token = tokenlambda;
		lambda->left = leftChild;
		leftChild->right = rightChild;
		stack.push(lambda);
	}

	return stack.pop();
}

//Node* stdOp(Node* node);

Node* StdAst::stdAnd(Node* node) {
	Node* equal = new Node;
	equal->token = Token("=", "=");
	Node* comma = new Node;
	comma->token = Token(",",",");
	Token tauToken("tau","tau");
	Node* tau = new Node;
	equal->left = comma;
	comma->right = tau;
	Node* andChild = node->left;
	queue<Node*> equalQueue;
	int tauCount = 0;
	while(andChild != NULL){
		equalQueue.push(andChild);
		andChild = andChild->right;
		tauCount++;
	}
	tauToken.taucount = tauCount;
	tau->token = tauToken;
	Node* currParam = NULL;
	Node* currValue = NULL;
	while(!equalQueue.empty()){
		Node* eqNode = equalQueue.front();
		equalQueue.pop();
		Node* param = eqNode->left;
		Node* value = eqNode->left->right;
		param->right = NULL;
		if(currParam == NULL){
			currParam = param;
			currValue = value;
			comma->left = currParam;
			tau->left = currValue;
		}else{
			currParam->right = param;
			currValue->right = value;
			currParam = param;
			currValue = value;
		}
	}

	return equal;
}

Node* StdAst::stdAt(Node* node) {
	Node* gamma1 = new Node;
	gamma1->token = tokengamma;
	Node* gamma2 = new Node;
	gamma2->token = tokengamma;
	gamma1->left = gamma2;
	Node* e2 = node->left->right->right;
	Node* n = node->left->right;
	n->right = NULL;
	Node* e1  = node->left;
	e1->right = NULL;
	gamma2->left = n;
	n->right = e1;
	gamma2->right = e2;

	return gamma1;
}

//Node* stdUop(Node* node);
