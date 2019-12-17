/*
 * Selector.cpp
 *
 *  Created on: 4 Dec 2019
 *      Author: james
 */

#include "Selector.h"

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "unistd.h"
#include "stdio.h"

#include "Content.h"
#include "VerbBase.h"
#include "ArgsParser.h"
#include "Component.h"

using namespace std;

Selector::Selector(const vector<string> &params,function<int(const string &output)> display)
{
	argsParser_ = make_shared<ArgsParser>(params);
	display_ = display;
}

int Selector::conjugate(function<void(shared_ptr<Content> content)> loadContent)
{
	if(!argsParser_->Valid()){
		cout << "Invalid arguments" << endl;
		return -1;
	}
	if(argsParser_->Infinitive().empty() && !argsParser_->Filename().empty()){
		return displayFileContents(loadContent);
	}
	// conjugate a single entry from the command line
	return conjugateVerb(argsParser_);
}

int Selector::displayFileContents(function<void(shared_ptr<Content> content)> loadContent)
{
	string wordtype = (argsParser_->Datatype()=="Verbs")?"":argsParser_->Wordtype();
	shared_ptr<Content> content;
	if(argsParser_->Datatype()=="Verbs"){
		content = make_shared<VerbContent>();}
	else {
		content = make_shared<GeneralContent>();}

	loadContent(content);
	return content->Display(wordtype,display_);
}

shared_ptr<VerbBase> Selector::BuildVerb(shared_ptr<ArgsParser> &argsParser)
{
	shared_ptr<VerbBase> inf 		 = make_shared<VerbBase>(argsParser->PsuedoInfinitive());
	shared_ptr<VerbBase> reflexive   = make_shared<ReflexiveDecorator>(inf);
	shared_ptr<VerbBase> vowelChange = make_shared<VowelDecorator>(reflexive,argsParser->Vowel());
	shared_ptr<VerbBase> conjugation = make_shared<ConjDecorator>(vowelChange);
	shared_ptr<VerbBase> stemChange  = make_shared<StemDecorator>(conjugation,argsParser->Stem());
	shared_ptr<VerbBase> negative    = make_shared<NegateDecorator>(stemChange,argsParser->Negate());
	shared_ptr<VerbBase> personForm	 = make_shared<PersonDecorator>(negative,argsParser->Person());
	shared_ptr<VerbBase> suppressed  = make_shared<SuppressDecorator>(personForm,argsParser->Suppress());
	return suppressed;
}

int Selector::conjugateVerb(shared_ptr<ArgsParser> &argsParser)
{
	shared_ptr<VerbBase> verb = BuildVerb(argsParser);
	auto x = verb->conjugate_struct(static_cast<VerbBase::Conjugation>(atoi(argsParser->Conjugation().c_str())));

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
	return display_(ss.str());
}
