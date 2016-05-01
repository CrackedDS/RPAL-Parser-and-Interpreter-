/*
 * scanner.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#include "scanner.h"

Scanner::Scanner() {

}

Scanner::Scanner(std::string code) {
	this->code = code;
	this->pos_ptr = 0;
	this->size = code.size();
}

Scanner::~Scanner() {

}

bool Scanner::isOperator(char ch) {
	char operators[] = {'+','-','*','<','>','&','.','@','/',':','=','-','|','$','!','#','%','^','_','[',']','{','}','"','`','?'};
	for(int i = 0; i < 26; i++) {
		if(ch == operators[i])
			return true;
	}
	return false;
}

bool Scanner::isKeyword(std::string st) {
	std::string keywords[] = {"let","where","aug","or","not","gr","ge","ls","le","eq","ne","true","false","nil","dummy","in","fn"
							,"within","and","rec","list"};
	int i;
	for(i=0;i<21;i++){
		if(st == keywords[i]){
			return true;
		}
	}
	return false;
}

Token Scanner::getNextToken() {
	Token token;

	while(true) {
		if(pos_ptr == size)
			throw "Nothing to fetch";
		char ch = code.at(pos_ptr++);
		if(isalpha(ch)) {
			token.value += ch;
			while(true) {
				if(pos_ptr != size) {
					ch = code.at(pos_ptr++);
					if(isalpha(ch) || isdigit(ch) || ch == '_')
						token.value += ch;
					else {
						pos_ptr--;
						break;
					}
				} else
					break;
			}
			if(isKeyword(token.value))
				token.type = "KEYWORD";
			else
				token.type = "IDENTIFIER";
		} else if(isdigit(ch)) {
			token.value += ch;
			while(true) {
				if(pos_ptr != size) {
					ch = code.at(pos_ptr++);
					if(isdigit(ch))
						token.value += ch;
					else {
						pos_ptr--;
						break;
					}
				} else
					break;
			}
			token.type = "INTEGER";
		} else if(isOperator(ch)) {
			if(ch == '/' && code.at(pos_ptr++) == '/') {
				while(code.at(pos_ptr++) != '\n') {
					//continue; ???? (make any difference)
				}
			} else {
				if(ch == '/')
					pos_ptr--;
				token.value += ch;
				while(true) {
					if(pos_ptr != size) {
						ch = code.at(pos_ptr++);
						if(isOperator(ch))
							token.value += ch;
						else {
							pos_ptr--;
							break;
						}
					} else
						break;
				}
				token.type = "OPERATOR";
			}
		} else if(ch == '\'') {
			token.value += ch;
			while(true) {
				if(pos_ptr != size) {
					ch = code.at(pos_ptr++);
					if(ch == '\\') {
						char ch1 = code.at(pos_ptr++);
						if(ch1 == 't' || ch1 == 'n' || ch1 == '\\' || ch1 == '\'') {
							token.value += ch;
							token.value += ch1;
						} else
							throw "Error in string format (lexer)";
					} else if(isalpha(ch) || isdigit(ch) || isOperator(ch) || ch =='(' || ch == ')' || ch == ',' || ch == ';' || isspace(ch)) {
						token.value += ch;
					} else if(ch == '\'') {
						token.value += ch;
						break;
					}
				} else
					break;
			}
			token.type = "STRING";
		} else if(isspace(ch) || ch == '\t' || ch == '\n') {
			continue;
		} else if (ch == '(' || ch == ')' || ch == ';' || ch == ',') {
			token.value = ch;
			token.type = ch;
		}
		return token;
	}
}

Token Scanner::peekNextToken(){
	if(pos_ptr == size)
		throw "No more tokens";
	Token temp = getNextToken();
	int count = temp.value.size();
	while(count-- !=0){
		pos_ptr--;
	}
	return temp;
}
