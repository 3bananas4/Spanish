//============================================================================
// Name        : LookupVerb.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Reads in a file, supplied on command line
//				 builds a dictionary of english-> spanish verb infinitives
//				 receives input from the user to define an English verb and a conjugation
// 				 then sends the spanish verb to std::out
//				 which can then be picked up by a piped app downstream
//============================================================================

#include <iostream>
#include <array>
#include "FileReader.h"
//#include "InfContent.h"
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <functional>

#include "Parser.h"
#include "Feeder.h"

using namespace std;

STRVEC collectArgs(int argc,char* argv[])
{
	STRVEC a;
	for(int i=0;i<argc;++i){
		a.emplace_back(argv[i]);
	}
	return a;
}

int main(int argc,char* argv[]) {

	STRVEC args = collectArgs(argc,argv);
	unsigned index=args[1][0]=='-'?3u:1u;

	Feeder feeder(args);
	FileReader f(args[index],[&feeder](const string & entry){
		auto parser = [](const string& s)->STRVEC{return LookupParser::Process(s);};
		feeder.addEntry(entry,parser);
	});

	if(args[1].compare("-i")==0){
		// interactive mode
		feeder.interactive(true,[](const string& s,char ch)->STRVEC{
			return Parser::Process(s,ch);});
	}
	else if(argc>3){
		// feed the pipe
		cout << feeder.feedPipe() << endl;
	}
}
