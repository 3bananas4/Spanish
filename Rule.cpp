/*
 * Rule.cpp
 *
 *  Created on: 26 Nov 2019
 *      Author: james
 */


#include <cctype>
#include <algorithm>
#include <sstream>

#include "Rule.h"
using namespace std;

Rule::Rule()
{

}

Rule::Rule(std::vector<Rule::RuleType> rules) : rules_(rules){
}

Rule::~Rule() {
}

string Rule::error()
{
	return error_;
}

bool Rule::test(const std::set<char> &flags,const std::vector<std::string> &options)
{
	return true;
}

//
FlagRule::FlagRule(char flag1,char flag2,vector<Rule::RuleType> rules)
: Rule(rules), f1_(flag1), f2_(flag2) {

}

//FlagRule::FlagRule(char flag1,char flag2) : f1_(flag1), f2_(flag2)
//{
//
//}

FlagRule::~FlagRule() {

}

string FlagRule::error()
{
	return error_;
//	string err;
//	if(rules_[0]==RuleType::EitherNotBoth){
//		err = "Flags '";
//		err += f1_;
//		err += "' and '";
//		err += f2_;
//		err += "' cannot be combined";
//	}
//	else {
//		err = "Using flag '";
//		err += f1_;
//		err += "' requires the usage also of flag '";
//		err += f2_;
//		err += "'";
//	}
//	return err;
}

bool FlagRule::test(const std::set<char> &flags,const std::vector<std::string> &options)
{
	if(rules_[0]==RuleType::EitherNotBoth){
		if(flags.find(f1_)==flags.end()) {
			return flags.find(f2_)!=flags.end();
		}
		return flags.find(f2_)==flags.end();
	}
	//
	if(flags.find(f1_)!=flags.end()){
		return flags.find(f2_)!=flags.end();
	}
	return true;
}

////////////////////////
OptionRule::OptionRule(char flag,vector<RuleType> rules)
: Rule(rules), flag_(flag){

}

OptionRule::~OptionRule() {

}

string OptionRule::error()
{
	string err;
//	if(ruletype_==RuleType::EitherNotBoth){
//		err = "Flags '";
//		err += f1_;
//		err += "' and '";
//		err += f2_;
//		err += "' cannot be combined";
//	}
//	else {
//		err = "Using flag '";
//		err += f1_;
//		err += "' requires the usage also of flag '";
//		err += f2_;
//		err += "'";
//	}
	return error_;
}

bool OptionRule::test(const std::set<char> &flags,const std::vector<std::string> &options)
{
	stringstream err;
	bool result(true);
	for(auto rule : rules_){
		if(result && flags.find(flag_)!=flags.end() && rule==Rule::RuleType::OptionCountExceedsOne){
			result &= options.size()>1;
			if(!result){err << "OptionCountExceedsOne" << ", ";}
		}
		if(result && flags.find(flag_)!=flags.end() && rule==Rule::RuleType::OptionCountExceedsTwo){
			result &= options.size()>2;
			if(!result){err << "OptionCountExceedsTwo" << ", ";}
		}
		if(result && flags.find(flag_)!=flags.end() && rule==Rule::RuleType::OptionCountExceedsThree){
			result &= options.size()>3;
			if(!result){err << "OptionCountExceedsThree" << ", ";}
		}
		if(result && flags.find(flag_)!=flags.end() && rule==Rule::RuleType::OptionThreeIsNumeral){
			if(options.size()<3 || !isdigit(options[2][0])){
				result &= false;
				if(!result){err << "OptionThreeIsNumeral: Option count " << options.size() << " Option[2] " << options[2] << ", ";}
			}
		}
		if(result && flags.find(flag_)!=flags.end() && rule==Rule::RuleType::OptionContainsUnderscore){
			// either the last or the penultimate option contains an underscore
			unsigned count=0;
			bool found(false);
			for(auto it=options.rbegin();it!=options.rend(),count<2;++it,++count)
			{
				if((*it).find('_')!=string::npos){
					result &= true;
					found=true;
				}
			}
			if(!found) {
				result &= false;
				if(!result){err << "OptionContainsUnderscore" << ", ";}
			}
		}
		if(result && flags.find(flag_)!=flags.end() && rule==Rule::RuleType::OptionCountExceedsFourIfC)
		{
			// get here only for 's' - check if 'c' exists
			if(flags.find('c')!=flags.end())
			{
				result &= options.size()>4;
				if(!result){err << "OptionCountExceedsFourIfC" << ", ";}
			}
		}
	}
	error_=err.str();
	return result;
}

