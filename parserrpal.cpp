/*
 * parserrpal.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#include <iostream>
#include "fileaccess.h"
#include <string.h>
#include <stdio.h>
#include "scanner.h"
#include "rdp.h"
#include "stdast.h"
#include "cse.h"

void printTree(Node* node, std::string dots) {
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
		printTree(node->left, dots1);
	if(node->right != NULL)
		printTree(node->right, dots);
}

int main(int argc,char *argv[]) {
	if(argc < 3){
		FileAccess fr(argv[argc-1]);
		string fileContent = fr.getFileContent();
		if(fileContent.size() == 0)
			return 0;

		Scanner scanner(fileContent);

		RDP parser(scanner);
		Node* ast_root = parser.parse();

//		View output of AST
//		parser.outputTree();

		StdAst stdast;
		Node* std_root = stdast.stdBegin(ast_root);

//		View output of standardized tree
//		printTree(std_root, "");

		CSE machine(std_root);
		machine.evaluateTree();

		return 0;
	}
	bool astFound = false;
	for(int j = 0; j < argc; j++) {
		if(strcmp(argv[j], "-ast") == 0) {
			astFound = true;
			break;
		}
	}
	if(astFound == true){
		FileAccess fr(argv[argc-1]);
		string fileContent = fr.getFileContent();
		if(fileContent.size() == 0)
			return 0;

		Scanner scanner(fileContent);

		RDP parser(scanner);
		Node* ast_root = parser.parse();
//		View output of AST
//		parser.outputTree();

		StdAst stdast;
		Node* std_root = stdast.stdBegin(ast_root);

//		View output of standardized tree
//		printTree(std_root, "");

		CSE machine(std_root);
		machine.evaluateTree();

	} else {
		//cout<< "check ---------"<<endl;
	}
	return 0;
}
