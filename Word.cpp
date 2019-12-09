/*
 * Word.cpp
 *
 *  Created on: 18 Nov 2019
 *      Author: james
 */

#include "Word.h"

using namespace std;

WordBase::WordBase() {
	// TODO Auto-generated constructor stub

}

WordBase::~WordBase() {
	// TODO Auto-generated destructor stub
}

Word::Word() : WordBase(){
	// TODO Auto-generated constructor stub

}

Word::~Word() {
	// TODO Auto-generated destructor stub
}

Word::Word(const vector<string> &content,std::function<vector<string>(const string&)> parse)
{
	for(auto s: content){
		auto res = parse(s);

		if(res[0].compare("english")==0){
			english=res[1];
		}
		else if(res[0].compare("foreign")==0){
			foreign=res[1];
		}
		else {
			wordtype=res[1];
		}
	}
}

Verb::Verb() {
	// TODO Auto-generated constructor stub

}

Verb::~Verb() {
	// TODO Auto-generated destructor stub
}

Verb::Verb(const vector<string> &content,std::function<vector<string>(const string&)> parse)
{

	//auto res = parse(content);
	for(auto s: content){
		auto res = parse(s);
		if(res.size()>1){
			english_ = res[0];
			conjugationRequest_ = res[1];
			//search this for spaces ?

			args_ = split(conjugationRequest_);
			args_.insert(args_.begin(),string("DummyBinary"));
		}
	}

}

std::vector<std::string> Verb::split(const std::string &input)
{
	char ch = ' ';
	size_t start=0;
	size_t end=input.find_first_of(ch);

	std::vector<std::string> output;
	while (end <= std::string::npos)
	{
		std::string s = input.substr(start, end-start);
		//trim(s);
		output.emplace_back(s);
		if (end == std::string::npos)
			break;

		start=end+1;
		end = input.find_first_of(ch, start);
	}

	return output;
}
