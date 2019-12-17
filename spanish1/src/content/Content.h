/*
 * Content.h
 *
 *  Created on: 25 Nov 2019
 *      Author: james
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#include <map>
#include <memory>
#include <string>
#include <functional>
#include <vector>
#include <sstream>

class WordBase;
class Word;
class Verb;

class Content {

public:
	Content();
	virtual ~Content();

	virtual void insert(
			const std::string& line,
			std::function<std::vector<std::string>(const std::string&)> parse)=0;
	virtual std::map<std::string,std::shared_ptr<WordBase> > Dictionary()=0;
	virtual int Display(
			const std::string &wordtype,
			std::function<int(const std::string & s)> output){return 0;};
};

class GeneralContent : public Content{

	std::map<std::string,std::shared_ptr<WordBase> > dictionary_;
public:
	GeneralContent();
	virtual ~GeneralContent();

	void insert(
			const std::string& line,
			std::function<std::vector<std::string>(const std::string&)> parse);
	std::map<std::string,std::shared_ptr<WordBase> > Dictionary(){return dictionary_;}

	int Display(
			const std::string &wordtype,
			std::function<int(const std::string & s)> output);
};


class VerbContent : public Content{

	std::map<std::string,std::shared_ptr<WordBase> > dictionary_;
public:
	VerbContent();
	virtual ~VerbContent();

	void insert(
			const std::string& line,
			std::function<std::vector<std::string>(const std::string&)> parse);
	std::map<std::string,std::shared_ptr<WordBase> > Dictionary(){return dictionary_;}

	int Display(
			const std::string &wordtype,
			std::function<int(const std::string & s)> output);
};

#endif /* CONTENT_H_ */
