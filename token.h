/*
 * token.h
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <vector>

class Token {
public:
	Token();
	Token(std::string value, std::string type); //Simple token constructor
	Token(std::string type,std::string lamdaParam, int lamdaNum);// Constructor for lambda closure
	Token(std::string type, int envNum ); // Constructor for environment
	Token(std::string type, int betaIfDeltaNum, int betaElseDeltaNum);
	virtual ~Token();
	std::string value;
	std::string type;
	int lambdaNum;
	std::string lambdaParam;
	int envNum;
	int betaIfDeltaNum;
	int betaElseDeltaNum;
	int taucount;
	bool isTuple;
	std::vector<Token> tuple;
	void construct();
	int lambdaEnv;
};

#endif /* TOKEN_H_ */
