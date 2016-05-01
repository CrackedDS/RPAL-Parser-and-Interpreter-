/*
 * rdp.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#include <iostream>
#include "rdp.h"
#include <cstdlib>

RDP::RDP(Scanner scanner) {
	this->scanner = scanner;
	moretokens = true;
}

RDP::RDP() {

}

RDP::~RDP() {

}

void RDP::read(Token token) {
	if(moretokens == false)
		throw "No more tokens to parse!";
	if(token.value != nexttoken.value) {
		std::exit(1);
	}
	if(token.type == "IDENTIFIER" || token.type == "STRING" || token.type == "INTEGER")
		buildTree(token, 0);
	try {
		nexttoken = scanner.getNextToken();
	} catch(const char* msg) {
		moretokens = false;
		nexttoken = Token("$", "$");
	}
}

void RDP::buildTree(Token token, int children) {
	Node* node = new Node;
	node->token = token;
	if(children != 0) {
		for(int i = 0; i < (children - 1); i++) {
			Node* child = stack.pop();
			stack.righttotop(child);
		}
		Node* firstchild = stack.pop();
		if(firstchild != NULL)
			node->left = firstchild;
	}
	stack.push(node);
}

void RDP::parseE() {
	if(nexttoken.value == "let") {
		read(nexttoken);
		parseD();
		read(Token("in", "KEYWORD"));
		parseE();
		Token nodetoken("let", "let");
		buildTree(nodetoken, 2);
	} else if(nexttoken.value == "fn") {
		read(nexttoken);
		int n = 0;
		do {
			parseVb();
			n++;
		} while(nexttoken.type == "IDENTIFIER" or nexttoken.type == "(");
		read(Token(".", "OPERATOR"));
		parseE();
		Token nodetoken("lambda", "lambda");
		buildTree(nodetoken, n+1);
	} else {
		parseEw();
	}
}

void RDP::parseEw() {
	parseT();
	if(nexttoken.value == "where") {
		read(nexttoken);
		parseDr();
		Token nodetoken("where", "where");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseT() {
	parseTa();
	if(nexttoken.value == ",") {
		int n = 0;
		do {
			read(nexttoken);
			parseTa();
			n++;
		} while(nexttoken.value == ",");
		Token nodetoken("tau", "tau");
		buildTree(nodetoken, n+1);
	}
}

void RDP::parseTa() {
	parseTc();
	while(nexttoken.value == "aug") {
		read(nexttoken);
		parseTc();
		Token nodetoken("aug", "KEYWORD");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseTc() {
	parseB();
	if(nexttoken.value == "->") {
		read(nexttoken);
		parseTc();
		read(Token("|", "OPERATOR"));
		parseTc();
		Token nodetoken("->", "->");
		buildTree(nodetoken, 3);
	}
}

void RDP::parseB() {
	parseBt();
	while(nexttoken.value == "or") {
		read(nexttoken);
		parseBt();
		Token nodetoken("or", "OPERATOR");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseBt() {
	parseBs();
	while(nexttoken.value == "&") {
		read(nexttoken);
		parseBs();
		Token nodetoken("&", "OPERATOR");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseBs() {
	if(nexttoken.value == "not") {
		read(nexttoken);
		parseBp();
		Token nodetoken("not", "not");
		buildTree(nodetoken, 1);
	} else {
		parseBp();
	}
}

void RDP::parseBp() {
	parseA();
	if(nexttoken.value == "gr" || nexttoken.value == ">") {
		read(nexttoken);
		parseA();
		Token nodetoken("gr", "OPERATOR");
		buildTree(nodetoken, 2);
	} else if(nexttoken.value == "ls" || nexttoken.value == "<") {
		read(nexttoken);
		parseA();
		Token nodetoken("ls", "OPERATOR");
		buildTree(nodetoken, 2);
	} else if(nexttoken.value == "ge" or nexttoken.value == ">=" ) {
		read(nexttoken);
		parseA();
		Token nodetoken("ge", "OPERATOR");
		buildTree(nodetoken, 2);
	} else if(nexttoken.value == "le" or nexttoken.value == "<=" ) {
		read(nexttoken);
		parseA();
		Token nodetoken("le", "OPERATOR");
		buildTree(nodetoken, 2);
	} else if(nexttoken.value == "eq" ) {
		read(nexttoken);
		parseA();
		Token nodetoken("eq", "OPERATOR");
		buildTree(nodetoken, 2);
	} else if(nexttoken.value == "ne") {
		read(nexttoken);
		parseA();
		Token nodetoken("ne", "OPERATOR");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseA() {
	if(nexttoken.value == "-") {
		read(Token("-", "OPERATOR"));
		parseAt();
		Token nodetoken("neg", "neg");
		buildTree(nodetoken, 1);
	} else if(nexttoken.value == "+") {
		read(Token("+", "OPERATOR"));
		parseAt();
	} else {
		parseAt();
	}
	while(nexttoken.value == "+" || nexttoken.value == "-") {
		Token temp = nexttoken;
		read(nexttoken);
		parseAt();
		Token nodetoken(temp.value, temp.type);
		buildTree(nodetoken, 2);
	}
}

void RDP::parseAt() {
	parseAf();
	while(nexttoken.value == "*" || nexttoken.value== "/") {
		Token temp = nexttoken;
		read(nexttoken);
		parseAf();
		Token nodetoken(temp.value, temp.type);
		buildTree(nodetoken, 2);
	}
}

void RDP::parseAf() {
	parseAp();
	while(nexttoken.value == "**") {
		Token temp = nexttoken;
		read(nexttoken);
		parseAf();
		buildTree(temp, 2);
	}
}

void RDP::parseAp() {
	parseR();
	while(nexttoken.value == "@") {
		read(nexttoken);
		if(nexttoken.type != "IDENTIFIER")
			throw "Expected Identifier found in parseAp()";
		read(nexttoken);
		parseR();
		Token nodetoken("@", "OPERATOR");
		buildTree(nodetoken,3);
	}
}

void RDP::parseR() {
	parseRn();
	while(nexttoken.type == "IDENTIFIER" || nexttoken.type == "STRING" || nexttoken.type == "INTEGER" ||
			nexttoken.value == "true" || nexttoken.value == "false" || nexttoken.value == "nil" ||
			nexttoken.value == "(" || nexttoken.value == "dummy") {
		parseRn();
		Token nodetoken("gamma", "gamma");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseRn() {
	if(nexttoken.type == "IDENTIFIER" || nexttoken.type == "STRING" || nexttoken.type == "INTEGER") {
		read(nexttoken);
	} else if(nexttoken.value == "true") {
		read(nexttoken);
		Token nodetoken("true", "true");
		buildTree(nodetoken, 0);
	} else if(nexttoken.value == "false") {
		read(nexttoken);
		Token nodetoken("false", "false");
		buildTree(nodetoken, 0);
	} else if(nexttoken.value == "nil") {
		read(nexttoken);
		Token nodetoken("nil", "nil");
		buildTree(nodetoken, 0);
	} else if(nexttoken.value == "dummy") {
		read(nexttoken);
		Token nodetoken("dummy", "dummy");
		buildTree(nodetoken, 0);
	} else if(nexttoken.value == "(") {
		read(nexttoken);
		parseE();
		read(Token(")", ")"));
	}
}

void RDP::parseD() {
	parseDa();
	if(nexttoken.value == "within") {
		read(nexttoken);
		parseD();
		Token nodetoken("within", "within");
		buildTree(nodetoken, 2);
	}
}

void RDP::parseDa() {
	parseDr();
	if(nexttoken.value == "and") {
		int n = 1;
		while(nexttoken.value == "and") {
			read(nexttoken);
			parseDr();
			n++;
		}
		Token nodetoken("and", "KEYWORD");
		buildTree(nodetoken, n);
	}
}

void RDP::parseDr() {
	if(nexttoken.value == "rec") {
		read(nexttoken);
		parseDb();
		Token nodetoken("rec", "KEYWORD");
		buildTree(nodetoken, 1);
	} else {
		parseDb();
	}
}

void RDP::parseDb() {
	if(nexttoken.value == "(") {
		read(nexttoken);
		parseD();
		read(Token(")", "OPERATOR"));
	} else if(nexttoken.type == "IDENTIFIER" && (scanner.peekNextToken().value == "," || scanner.peekNextToken().value == "=")) {
		parseV1();
		read(Token("=", "OPERATOR"));
		parseE();
		Token nodetoken("=", "=");
		buildTree(nodetoken, 2);
	} else {
		read(nexttoken);
		int n = 1;
		parseVb();
		while(nexttoken.type == "IDENTIFIER" or nexttoken.value == "(") {
			n++;
			parseVb();
		}
		read(Token("=", "OPERATOR"));
		parseE();
		Token nodetoken("function_form", "function_form");
		buildTree(nodetoken, n+2);
	}
}

void RDP::parseVb() {
	if(nexttoken.type == "IDENTIFIER") {
		read(nexttoken);
	} else if(nexttoken.value == "(") {
		read(nexttoken);
		if(nexttoken.value == ")") {
			read(nexttoken);
			Token nodetoken("()", "()");
			buildTree(nodetoken, 0);
		} else {
			parseV1();
			read(Token(")", ")"));
		}
	}
}

void RDP::parseV1() {
	read(nexttoken);
	int n = 1;
	if(nexttoken.value == ",") {
		while(nexttoken.value == ",") {
			n++;
			read(nexttoken);
			read(nexttoken);
		}
		Token nodetoken(",", ",");
		buildTree(nodetoken, n);
	}
}

void RDP::order(Node* node, std::string dots) {
	if(node->token.type == "IDENTIFIER") {
		std::cout << dots << "<ID:" << node->token.value << '>' << std::endl;
	} else if(node->token.type == "INTEGER") {
		std::cout << dots<< "<INT:" << node->token.value << '>' << std::endl;
	} else if(node->token.type == "STRING") {
		std::cout << dots << "<STR:" << node->token.value << '>' << std::endl;
	} else if(node->token.value == "true" || node->token.value == "false" || node->token.value == "nil" || node->token.value == "dummy") {
		std::cout << dots << '<' << node->token.value << '>' << std::endl;
	} else {
		std::cout << dots << node->token.value << std::endl;
	}
	std::string dots1 = "." + dots;
	if(node->left != NULL)
		order(node->left, dots1);
	if(node->right != NULL)
		order(node->right, dots);
}

void RDP::outputTree() {
	Node* node = stack.pop();
	order(node, std::string(""));
}

Node* RDP::parse() {
	nexttoken = scanner.getNextToken();
	parseE();
	return stack.getTop();
}
