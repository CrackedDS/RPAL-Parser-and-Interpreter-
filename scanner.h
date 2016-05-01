/*
 * scanner.h
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#ifndef SCANNER_H_
#define SCANNER_H_

#include <string>
#include "token.h"

class Scanner {
private:
	std::string code;
	int size;
	int pos_ptr;
	bool isOperator(char ch);
	bool isKeyword(std::string st);
public:
	Scanner();
	Scanner(std::string code);
	virtual ~Scanner();
	Token getNextToken();
	Token peekNextToken();
};

#endif /* SCANNER_H_ */
