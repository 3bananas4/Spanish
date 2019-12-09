/*
 * InfContent.cpp
 *
 *  Created on: 2 Dec 2019
 *      Author: james
 */

#include "InfContent.h"
#include <vector>
//#include <iostream>

using namespace std;

InfContent::InfContent() {
	// TODO Auto-generated constructor stub

}

InfContent::~InfContent() {
	// TODO Auto-generated destructor stub
}

void InfContent::insert(const string &entry,function<vector<string>(const string&)> parse)
{
	auto response = parse(entry);
	if(response.size()>1){
		auto engl = response[0];
		response.erase(response.begin());
		dictionary_[engl]=response;
	}

}
