/*
 * rdp.h
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#ifndef RDP_H_
#define RDP_H_

#include "scanner.h"
#include "stack.h"

class RDP {
private:
	Scanner scanner;
	bool moretokens;
	Token nexttoken;
	void read(Token token);
	void buildTree(Token token, int children);
	void parseE();
	void parseEw();
	void parseT();
	void parseTa();
	void parseTc();
	void parseB();
	void parseBt();
	void parseBs();
	void parseBp();
	void parseA();
	void parseAt();
	void parseAf();
	void parseAp();
	void parseR();
	void parseRn();
	void parseD();
	void parseDa();
	void parseDr();
	void parseDb();
	void parseVb();
	void parseV1();
	void order(Node* node, std::string dots);
public:
	RDP();
	RDP(Scanner scanner);
	~RDP();
	Stack stack;
	void outputTree();
	Node* parse();
};

#endif /* RDP_H_ */
