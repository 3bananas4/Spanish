/*
 * Selector.cpp
 *
 *  Created on: 4 Dec 2019
 *      Author: james
 */

#include "Selector.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <memory>
#include <cstdlib>
#include <vector>
#include <functional>

#include "FileReader.h"
#include "Content.h"
#include "Parser.h"
#include "VerbBase.h"
#include "ArgsParser.h"
#include "Word.h"
#include "Component.h"
#include "unistd.h"
#include "stdio.h"

using namespace std;
//Selector::Selector() {
//	// TODO Auto-generated constructor stub
//
//}

Selector::Selector(const vector<string> &params,function<void(const string &output)> display)
{
	argsParser_ = make_shared<ArgsParser>(params);
	display_ = display;
}

//Selector::~Selector() {
//	// TODO Auto-generated destructor stub
//}

int Selector::conjugate()
{
	if(!argsParser_->Valid()){
		return -1;
	}
	if(argsParser_->Infinitive().empty() && !argsParser_->Filename().empty()){
		return displayFileContents();
	}
	// conjugate a single entry from the command line
	return conjugateVerb(argsParser_);
}

int Selector::displayFileContents()
{
	if(argsParser_->Datatype()=="Verbs")
	{
		display(
			make_shared<VerbContent>(),
			[this](shared_ptr<Content>& content){
				auto parser = [](const string& s){return VerbParser::Process(s);};
				FileReader fr(argsParser_->Filename(),[&content,&parser](const std::string& a){content->insert(a,parser);});
			},"");
	}
	else
	{
		display(
			make_shared<GeneralContent>(),
			[this](shared_ptr<Content>& content){
				auto parser = [](const string& s){return WordParser::Process(s);};
				FileReader fr(argsParser_->Filename(),[&content,&parser](const std::string& a){content->insert(a,parser);});
			},
			argsParser_->Wordtype());
	}
	return 0;
}

int Selector::conjugateVerb(shared_ptr<ArgsParser> &argsParser)
{
	shared_ptr<VerbBase> inf = make_shared<VerbBase>(argsParser->PsuedoInfinitive());

	shared_ptr<VerbBase> reflexive   = make_shared<ReflexiveDecorator>(inf);
	shared_ptr<VerbBase> vowelChange = make_shared<VowelDecorator>(reflexive,argsParser->Vowel());

	shared_ptr<VerbBase> conj;
	string vbtype = VerbBase::verbType(argsParser->PsuedoInfinitive());
	if(vbtype.compare("ar")==0)		{ conj= make_shared<ARVerbDecorator>(vowelChange); }
	else if(vbtype.compare("er")==0){ conj= make_shared<ERVerbDecorator>(vowelChange); }
	else if(vbtype.compare("ir")==0){ conj= make_shared<IRVerbDecorator>(vowelChange); }

	shared_ptr<VerbBase> stemChange  = make_shared<StemDecorator>(conj,argsParser->Stem());
	shared_ptr<VerbBase> negative    = make_shared<NegateDecorator>(stemChange,argsParser->Negate());
	shared_ptr<VerbBase> personForm	 = make_shared<PersonDecorator>(negative,argsParser->Person());
	shared_ptr<VerbBase> suppressed  = make_shared<SuppressDecorator>(personForm,argsParser->Suppress());

	auto x = suppressed->conjugate_struct(static_cast<VerbBase::Conjugation>(atoi(argsParser->Conjugation().c_str())));

	stringstream ss;
	for(auto c: x){

		if(argsParser->Structure()){
			ss << "[("+c->Part() + ")";
		}
		ss << c->Value();
		if(argsParser->Structure()){
			ss << "]";
		}
		else if(c!=x.back() && !(c->Part().compare("Pronoun")==0 && c->Value().empty())){
			ss << " ";
		}
	}
	display_(ss.str());
	return 0;
}

int Selector::display(
		shared_ptr<Content> content,
		function<void(shared_ptr<Content>& content)> load,
		const string & wordType)
{
	load(content);
	content->Display(wordType,display_);
	return 0;
}
