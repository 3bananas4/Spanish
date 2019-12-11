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
#include "../content/Selector.h"
#include "../content/ArgsParser.h"

using namespace std;

int main(int argc,char *argv[]) {

	vector<string> params;
	for(int index=0;index<argc;++index){
		params.emplace_back(argv[index]);
	}

	auto display = [](const string &output){cout << output << endl;};
	Selector sel(params,display);
	if( isatty(fileno(stdin))){
		return sel.conjugate(/*display*/); // run directly from the command line
	}

	string lineInput;
	// received piped input - getline retrieves the output of the upstream application
	if (getline(cin,lineInput)) {
		shared_ptr<ArgsParser> ap = make_shared<ArgsParser>(lineInput);
		if(!ap->Valid()){
			cout << "Invalid input" << endl;
			return -1;
		}
		sel.conjugateVerb(ap/*,display*/);//[](const string &output){cout << output << endl;});
	}
	return 0;
}
