//============================================================================
// Name        : spanish1.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "unistd.h"
#include "stdio.h"
#include "Selector.h"
#include "ArgsParser.h"
#include "FileReader.h"
#include "Content.h"
#include "Parser.h"

using namespace std;

int error(const string &msg)
{
	cout << msg << endl;
	return -1;
}

int commandLineFeed(Selector & sel)
{
	auto parser = [](const string& s){return Parser::Process(s);};
	auto loader = [&parser,&sel](shared_ptr<Content> content){
		FileReader fr(
			sel.Arguments()->Filename(),
			[&parser,&content](const std::string& a){content->insert(a,parser);});
	};
	return sel.conjugate(loader);
}

int pipeFeed(Selector & sel)
{
	// received piped input - getline retrieves the output of the upstream application
	string lineInput;
	if (!getline(cin,lineInput)) {
		return error("Invalid input");
	}

	shared_ptr<ArgsParser> ap = make_shared<ArgsParser>(lineInput);
	if(!ap->Valid()){
		return error("Invalid input");
	}
	return sel.conjugateVerb(ap);
}

int main(int argc,char *argv[]) {

	vector<string> params;
	for(int index=0;index<argc;++index){
		params.emplace_back(argv[index]);
	}

	Selector sel(params,[](const string &output)-> int {cout << output << endl;return 0;});
	if( isatty(fileno(stdin))){
		return commandLineFeed(sel);
	}

	return pipeFeed(sel);
}
