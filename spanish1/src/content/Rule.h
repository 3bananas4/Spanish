/*
 * Rule.h
 *
 *  Created on: 26 Nov 2019
 *      Author: james
 */

#ifndef RULE_H_
#define RULE_H_

#include <set>
#include <string>
#include <vector>
#include <initializer_list>

class Rule {
protected:
	std::string error_;
public:
	enum RuleType {
		EitherNotBoth,
		IfFirstSecond,
		OptionCountExceedsOne,
		OptionCountExceedsTwo,
		OptionThreeIsNumeral,
		OptionCountExceedsThree,
		OptionCountExceedsFour,
		OptionContainsUnderscore,
		OptionCountExceedsFourIfC};

	Rule();
	Rule(std::vector<Rule::RuleType> rules);
	virtual ~Rule();

	virtual bool test(const std::set<char> &flags,const std::vector<std::string> &options={});
	virtual std::string error();

protected:
	std::vector<Rule::RuleType> rules_;
};

class FlagRule : public Rule {
	char f1_;
	char f2_;
public:
	FlagRule(char flag1,char flag2,std::vector<Rule::RuleType> rules);
	//FlagRule(char flag1,char flag2);
	virtual ~FlagRule();

	virtual bool test(const std::set<char> &flags,const std::vector<std::string> &options={});
	virtual std::string error();
};

class OptionRule : public Rule {
	char flag_;

public:
	OptionRule(char flag,std::vector<RuleType> rules);
	virtual ~OptionRule();

	virtual bool test(const std::set<char> &flags,const std::vector<std::string> &options={});
	virtual std::string error();
};

#endif /* RULE_H_ */
