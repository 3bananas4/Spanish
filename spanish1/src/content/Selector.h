/*
 * Selector.h
 *
 *  Created on: 4 Dec 2019
 *      Author: james
 */
#ifndef SELECTOR_H_
#define SELECTOR_H_

#include <memory>
#include <vector>
#include <functional>
#include <string>

class ArgsParser;
class Content;

class Selector {
	std::shared_ptr<ArgsParser> argsParser_;

	int displayFileContents();
	//int conjugateVerb();



public:
	Selector(){}
	Selector(const std::vector<std::string> &params);
	virtual ~Selector(){}

	int conjugate();
	int conjugateVerb(std::shared_ptr<ArgsParser> &argsParser,std::function<void(const std::string &)> output);

	int displayVerbs(std::function<void(std::shared_ptr<Content>& content)> load,std::function<void(const std::string &output)> display);
	int displayWords(std::function<void(std::shared_ptr<Content>& content)> load,const std::string & wordType,std::function<void(const std::string &output)> display);

	int testFunction(int value){return 2*value;}
};

#endif /* SELECTOR_H_ */
