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

class Selector {
	std::shared_ptr<ArgsParser> argsParser_;
	std::function<void(const std::string &output)> display_;

	int displayFileContents();
	std::shared_ptr<VerbBase> BuildVerb(std::shared_ptr<ArgsParser> &argsParser);

public:
	Selector(){}
	Selector(const std::vector<std::string> &params,std::function<void(const std::string &output)> display);
	virtual ~Selector(){}

	int conjugate();
	int conjugateVerb(std::shared_ptr<ArgsParser> &argsParser);

	int display(
		std::shared_ptr<Content> content,
		std::function<void(std::shared_ptr<Content>& content)> load,
		const std::string & wordType);
	int testFunction(int value){return 2*value;}
};

#endif /* SELECTOR_H_ */
