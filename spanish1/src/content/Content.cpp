/*
 * Content.cpp
 *
 *  Created on: 25 Nov 2019
 *      Author: james
 */

#include "Content.h"
#include "Word.h"

#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

Content::Content() {
	// TODO Auto-generated constructor stub

}

Content::~Content() {
	// TODO Auto-generated destructor stub
}

GeneralContent::GeneralContent() {
	// TODO Auto-generated constructor stub

}

GeneralContent::~GeneralContent() {
	// TODO Auto-generated destructor stub
}

void GeneralContent::insert(const string &entry,function<vector<string>(const string&)> parse)
{
	size_t start=0;
	size_t end=entry.find_first_of(',');

	vector<string> output;
	while (end <= string::npos)
	{
		output.emplace_back(entry.substr(start, end-start));

		if (end == string::npos)
			break;

		start=end+1;
		end = entry.find_first_of(',', start);
	}

	shared_ptr<Word> w = make_shared<Word>(output,parse);
	dictionary_[w->English()]=w;

	//cout << "Word : " << w->English() << " " << w->Foreign() << endl;
}

void GeneralContent::Display(const std::string &wordtype,function<void(const string & s)> output)
{
	for(auto it=dictionary_.begin();it!=dictionary_.end();++it){
		shared_ptr<Word> word=dynamic_pointer_cast<Word>(it->second);
		if(wordtype.compare("All")==0 || word->Wordtype().compare(wordtype)==0){

			string type = wordtype.compare("All")==0? ", Wordtype: " + word->Wordtype() : "";

			stringstream ss;
			ss << "English: " << it->first << ", Spanish: " << word->Foreign() << type;
			output(ss.str());
		}
	}
}
//
//void Content::ShowKeys(const std::string &wordtype)
//{
//	for(auto it=dictionary.begin();it!=dictionary.end();++it){
//		if(wordtype.compare("All")==0 || it->second->Wordtype().compare(wordtype)==0){
//
//			string type = wordtype.compare("All")==0? ", Wordtype: " + it->second->Wordtype() : "";
//
//			cout
//				<< "Key: "
//				<< it->first
//				<< ", Spanish: "
//				<< it->second->Foreign()
//				<< type
//				<< endl;
//		}
//	}
//}

//////
VerbContent::VerbContent() {
	// TODO Auto-generated constructor stub

}

VerbContent::~VerbContent() {
	// TODO Auto-generated destructor stub
}

void VerbContent::insert(const string &entry,function<vector<string>(const string&)> parse)
{
	size_t start=0;
	size_t end=entry.find_first_of(',');

	vector<string> output;
	while (end <= string::npos)
	{
		output.emplace_back(entry.substr(start, end-start));

		if (end == string::npos)
			break;

		start=end+1;
		end = entry.find_first_of(',', start);
	}

	shared_ptr<Verb> v = make_shared<Verb>(output,parse);
	if(!v->English().empty()){
		dictionary_[v->English()]=v;
	}
}

void VerbContent::Display(const std::string &wordtype,function<void(const string & s)> output)
{
	for(auto it=dictionary_.begin();it!=dictionary_.end();++it){
		stringstream ss;
		shared_ptr<Verb> verb=dynamic_pointer_cast<Verb>(it->second);
		ss << verb->English() << " : " << verb->Args()[2];
		output(ss.str());
	}
}
