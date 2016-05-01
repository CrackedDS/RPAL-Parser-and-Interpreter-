/*
 * fileaccess.h
 *
 *  Created on: Apr 21, 2016
 *      Author: deepa
 */

#ifndef FILEACCESS_H_
#define FILEACCESS_H_

#include <string>

class FileAccess {
private:
	char* file;
public:
	FileAccess(char* file);
	std::string getFileContent();
};

#endif /* FILEACCESS_H_ */
