/*
 * fileaccess.cpp
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#include "fileaccess.h"
#include <iostream>
#include <fstream>
using namespace std;

FileAccess::FileAccess(char* file) {
	this->file = file;
}

std::string FileAccess::getFileContent() {
	std::string content;
	std::string temp;
	ifstream filename;
	filename.open(this->file, ios::in);
	if(filename.is_open()) {
		while(filename.good()) {
			getline(filename, temp);
			content += temp + '\n';
		}
	} else {
		cerr << "Error opening the file";
	}
	return content;
}
