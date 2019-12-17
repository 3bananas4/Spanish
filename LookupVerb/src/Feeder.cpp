/*
 * Feeder.cpp
 *
 *  Created on: 15 Dec 2019
 *      Author: james
 */

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Feeder.h"

using namespace std;
Feeder::Feeder() {
	// TODO Auto-generated constructor stub

}

Feeder::Feeder(const std::vector<std::string> &args)
: args_(args)
{

}

Feeder::~Feeder() {}

void Feeder::addEntry(const string &entry,function<STRVEC(const string& s)> parser)
{
	auto response = parser(entry);
	if(response.size()>1){
		dict_[response[0]]=STRVEC(response.begin()+1,response.end());
	}
}

string Feeder::composeCommand(const STRVEC &filecommands,const string &conjugation)
{
	stringstream ss;
	ss << filecommands[0] << " " << filecommands[1] << " " << conjugation;
	for(unsigned index = 3;index<filecommands.size();++index){
		ss << " " << filecommands[index];
	}
	return ss.str();
}

string Feeder::feedPipe()
{
	return composeCommand( dict_[args_[2]],args_[3] );
}

void Feeder::runPrompt(bool showPrompt,function<bool(const string&)> process)
{
	if(showPrompt){
		cout << ":";
	}
	string lineInput;
	while(	getline(cin,lineInput) && process(lineInput)) {
		if(showPrompt){
			cout << ":";
		}
	}
}

int Feeder::openApp(const string &command)
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

bool Feeder::processLine(
		const string &lineInput,
		function<STRVEC(const string &,char)> parse,
		function<string(const STRVEC&)> compose)
{
	if(lineInput.compare("q")==0){
		return false;
	}

	try {
		auto userparams = parse(lineInput,' ');
		openApp( compose(userparams) );
	}
	catch(std::exception &e) {
		cout << e.what() << endl;
		return false;}

	return true;
}

void Feeder::interactive(bool showPrompt,std::function<STRVEC(const std::string&,char)> parser)
{
	auto c = [this](const STRVEC& userparams)->string{
		stringstream s;
		s << "./" << args_[2] << " " << composeCommand(dict_[userparams[0]],userparams[1]);
		return s.str();
	};

	runPrompt(showPrompt,[&parser,&c,this](const string& line)->bool{ return processLine(line,parser,c); });
}
