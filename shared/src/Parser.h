/*
 * Parser.h
 *
 *  Created on: 25 Nov 2019
 *      Author: james
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <locale>

class Parser {

public:
	// trim from start (in place)
	static inline void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
			return !std::isspace(ch);
		}));
	}

	// trim from end (in place)
	static inline void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
			return !std::isspace(ch);
		}).base(), s.end());
	}

	// trim from both ends (in place)
	static inline void trim(std::string &s) {
		ltrim(s);
		rtrim(s);
	}

	static inline std::string stripCharacters(const std::string& input)
	{
		std::string after(input),before;
		std::vector<char> chars = {'{','}','\"'};

		for(auto ch : chars){
			do
			{
				before=after;
				size_t found = after.find(ch);
				if(found!=std::string::npos){
					after.erase(found,1);
				}
			}while(before!=after);
		}
		return after;
	}

	static inline std::vector<std::string> split(const std::string &input,char ch=':')
	{
		size_t start=0;
		size_t end=input.find_first_of(ch);

		std::vector<std::string> output;
		while (end <= std::string::npos)
		{
			std::string s = input.substr(start, end-start);
			trim(s);
			output.emplace_back(s);
			if (end == std::string::npos)
				break;

			start=end+1;
			end = input.find_first_of(ch, start);
		}

		return output;
	}

	Parser();
	virtual ~Parser();

	static inline std::vector<std::string> Process(const std::string & input,char ch=':')
	{
		std::string output = stripCharacters(input);
		return split(output,ch);
	}
};

class LookupParser : public Parser {
public:
	LookupParser(){}
	virtual ~LookupParser(){}

	static inline std::vector<std::string> Process(const std::string & input)
	{
		std::string output = stripCharacters(input);
		auto t1 =  split(output,':');
		auto t2 =  split(t1[1],' ');
		t2.insert(t2.begin(),t1[0]);
		return t2;
	}
};
/*
class VerbParser : public Parser {
public:
	VerbParser(){}
	virtual ~VerbParser(){}

		static inline std::vector<std::string> split(const std::string &input,char ch=':')
	{
		size_t start=0;
		size_t end=input.find_first_of(ch);

		std::vector<std::string> output;
		while (end <= std::string::npos)
		{
			std::string s = input.substr(start, end-start);
			trim(s);
			output.emplace_back(s);
			if (end == std::string::npos)
				break;

			start=end+1;
			end = input.find_first_of(ch, start);
		}

		return output;
	}

	static inline std::vector<std::string> Process(const std::string & input)
	{
		std::string output = Parser::stripCharacters(input);
		return VerbParser::split(output);
	}

};

class WordParser : public Parser {
public:
	WordParser(){}
	virtual ~WordParser(){}

	static inline std::vector<std::string> split(const std::string &input,char ch = ':')
	{
		size_t start=0;
		size_t end=input.find_first_of(ch);

		std::vector<std::string> output;
		while (end <= std::string::npos)
		{
			std::string s = input.substr(start, end-start);
			trim(s);
			output.emplace_back(s);
			if (end == std::string::npos)
				break;

			start=end+1;
			end = input.find_first_of(ch, start);
		}

		return output;
	}

	static inline std::vector<std::string> Process(const std::string & input)
	{
		std::string output = Parser::stripCharacters(input);
		return WordParser::split(output);
	}

};
*/
/* Need this from the Lookup form of the Parser
 * ALso uses the second form of process in the base class
 static inline std::vector<std::string> Process(const std::string & input)
	{
		std::string output = stripCharacters(input);
		auto t1 =  split(output,':');
		auto t2 =  split(t1[1],' ');
		t2.insert(t2.begin(),t1[0]);
		return t2;
	}
 */

#endif /* PARSER_H_ */
