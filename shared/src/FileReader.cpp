/*
 * FileReader.cpp
 *
 *  Created on: 18 Nov 2019
 *      Author: james
 */
#include "FileReader.h"

#include <fstream>
#include <string>

using namespace std;

FileReader::FileReader(const string &filename,function<void(const std::string&)> store)
{
	/*
	 * wanted to convert to for_each with a lambda
	 * but this needs an iterator rather than getline, so no dice
	 */
	ifstream filein(filename);
	for (string line; getline(filein, line); )
	{
		store(line);
	}
}
