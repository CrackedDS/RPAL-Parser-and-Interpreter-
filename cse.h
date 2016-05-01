/*
 * cse.h
 *
 *  Created on: Apr 27, 2016
 *      Author: deepa
 */

#ifndef CSE_H_
#define CSE_H_

#include <map>
#include <stack>
#include "Token.h"
#include "Node.h"
#include <list>
#include <vector>
#include <queue>
#include <sstream>
#include <utility>

using namespace std;
typedef map<string,Token> envMap;
typedef pair<int,string> keyPair;

class CSE {
public:
	CSE();
	CSE(Node* input);
	virtual ~CSE();
	void evaluateTree();
private:
	map<int, vector<Token> > deltaMap;
	ostringstream oss;
	int deltaCounter;
	int currDeltaNum;
	int envCounter;
	queue<Node*> pendingDeltaQueue;
	Node* inputTree;
	//map<int, envMap> paramMap;
	map<keyPair,Token> paramMap;
	void createControlStructures(Node* root);
	void preOrderTraversal(Node* root, vector<Token> &currentDelta);
	void processCurrentToken(Token &currToken, stack<Token> &controlStack, stack<Token> &executionStack);
	Token applyOperator(Token firstToken, Token secondToken, Token currToken);
	string intToString(int intValue);
	vector<string> split(string inputString, char delimiter);
	bool notFunction(string value);
	bool isParamter(Token currToken);
	map<int,int> envMap;
	stack<int> envStack;
	int currEnv;
	bool printCalled;
	string unescape(const string& s);
	void printTuple(Token t);
};



#endif /* CSE_H_ */
