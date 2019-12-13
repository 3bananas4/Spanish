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
class VerbBase;
class Parser;

class Selector {
	std::shared_ptr<ArgsParser> argsParser_;
	std::function<void(const std::string &output)> display_;

	int displayFileContents(std::function<void(std::shared_ptr<Content> content)> loadContent);
	std::shared_ptr<VerbBase> BuildVerb(std::shared_ptr<ArgsParser> &argsParser);

public:
	Selector(){}
	Selector(const std::vector<std::string> &params,std::function<void(const std::string &output)> display);
	virtual ~Selector(){}

	int conjugate(std::function<void(std::shared_ptr<Content> content)> loadContent);
	int conjugateVerb(std::shared_ptr<ArgsParser> &argsParser);

	int testFunction(int value){return 2*value;}

	std::shared_ptr<ArgsParser> Arguments() const {return argsParser_;}
};

#endif /* SELECTOR_H_ */
