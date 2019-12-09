/*
 * FileReader.h
 *
 *  Created on: 18 Nov 2019
 *      Author: james
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <functional>

class FileReader
{
public:
	FileReader(const std::string &filename,std::function<void(const std::string&)> store);
};

#endif /* FILEREADER_H_ */
