/*
 * Word.h
 *
 *  Created on: 18 Nov 2019
 *      Author: james
 */

#ifndef WORD_H_
#define WORD_H_

#include <string>
#include <vector>
#include <functional>

class WordBase {
public:
	WordBase();
	virtual ~WordBase();
};

class Word : public WordBase{

	std::string english;
	std::string foreign;
	std::string wordtype;

public:
	Word();
	Word(const std::vector<std::string> &content,std::function<std::vector<std::string>(const std::string&)> parse);
	virtual ~Word();

	inline std::string English() { return english; }
	inline std::string Foreign() { return foreign; }
	inline std::string Wordtype() { return wordtype; }
};

class Verb : public WordBase {

	std::string english_;
	std::string conjugationRequest_;
	std::vector<std::string> args_;


	std::vector<std::string> split(const std::string &input);

public:
	Verb();
	Verb(const std::vector<std::string> &content,std::function<std::vector<std::string>(const std::string&)> parse);
	virtual ~Verb();

	inline std::string English() { return english_; }
	std::vector<std::string> Args() {return args_;}
};

#endif /* WORD_H_ */
