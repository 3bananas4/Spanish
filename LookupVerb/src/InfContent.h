/*
 * InfContent.h
 *
 *  Created on: 2 Dec 2019
 *      Author: james
 */

#ifndef INFCONTENT_H_
#define INFCONTENT_H_

#include <string>
#include <map>
#include <functional>
#include <vector>

class InfContent {
	std::map<std::string,std::vector<std::string>> dictionary_;
public:
	InfContent();
	virtual ~InfContent();

	void insert(const std::string& line,std::function<std::vector<std::string>(const std::string&)> parse);
	//std::map<std::string,std::string> Content(){return dictionary_;}
	std::vector<std::string> Lookup(const std::string &english) const {
		if( dictionary_.find(english)==dictionary_.end()){
			return {};
		}
		return dictionary_.at(english);
	}
};

#endif /* INFCONTENT_H_ */
