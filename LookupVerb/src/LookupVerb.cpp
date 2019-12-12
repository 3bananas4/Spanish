//============================================================================
// Name        : LookupVerb.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Reads in a file, supplied on command line
//				 builds a dictionary of englihs-> spanish verb infinitives
//				 receives input from the user to define an English verb and a conjugation
// 				 then sends the spanish verb to std:: out
//				 which can then be picked up by a piped app downstream
//============================================================================

#include <iostream>
#include <array>
#include "FileReader.h"
#include "InfContent.h"
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <functional>
#include "Parser.h"

using namespace std;

int feedPipe(const std::vector<std::string> &params,const string &conjugation)
{
	if(params.size()<3){
		return -1;
	}
	cout << params[0] << " " << params[1] << " " << conjugation;
	unsigned index = 3;
	for(;index<params.size();++index){
		cout << " " << params[index];
	}
	cout << endl;
	return 0;
}

string createCommand(const std::string &appName,const std::vector<std::string> &fileparams,const string &conjugation)
{
	stringstream s;
	try {
		s << appName << " " << fileparams[0] << " " << fileparams[1] << " " << conjugation << " ";
		// add any further parameters required from the file e.g. 'e_ie'
		for(unsigned index=3;index<fileparams.size();++index){
			s << fileparams[index];
			if( index<fileparams.size()-1){
				s << " ";
			}
		}
	}
	catch(std::exception &e)
	{
		cout << e.what() << endl;
	}
	return s.str();
}

int openApp(const string &command)
{
	array<char, 128> buffer;
	string result;
	try {

		auto pipe = popen(command.c_str(), "r" );
		if (!pipe) throw runtime_error("popen() failed!");

		while (!feof(pipe)) {
			if (fgets(buffer.data(), 128, pipe) != nullptr)
				result += buffer.data();
		}

		/*auto rc = */pclose(pipe);
		cout << result << endl;
	}
	catch(exception &e)
	{
		cout << e.what() << endl;
	}
	return 0;
}

int interactiveMode(
		const std::string &app,
		function<vector<string>(const string&)> lookup,
		function<vector<string>(const string &,char)> parser)
{
	cout << ":";
	string lineInput;
	while(getline(cin,lineInput)) {
		if(lineInput.compare("q")==0){
			break;
		}
		auto userparams = parser(lineInput,' ');
		if(userparams.size()<2u){
			cout << "Please ensure both an infinitive and a conjugation form are provided e.g. make 1" << endl << ":";
		}
		else {
			openApp( createCommand("./"+app,lookup(userparams[0]),userparams[1]) );
			cout << ":";
		}
	}
	return 0;
}

int main(int argc,char* argv[]) {

	InfContent content;
	auto parser = [](const string& s){return LookupParser::Process(s);};
	unsigned index=1;
	if(argv[1][0]=='-'){
		index=3;
	}
	FileReader fr(argv[index],[&content,&parser](const std::string& a){content.insert(a,parser);});

	// interactive mode with inner command prompt - ./Lookup -i app verbs.json
	if(strcmp(argv[1],"-i")==0){
		interactiveMode(
			argv[2],
			[&content](const string& english){return content.Lookup(english);},
			[](const string& s,char ch){return Parser::Process(s,ch);});
	}
	// generate input to downstream pipe into app - ./Lookup verbs.json have 2
	else if(argc>3){
		feedPipe(content.Lookup(static_cast<string>(argv[index+1])),argv[3]);
	}

	return 0;
}
