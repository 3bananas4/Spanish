/*
 * ArgsParser.h
 *
 *  Created on: 26 Nov 2019
 *      Author: james
 */

#ifndef ARGSPARSER_H_
#define ARGSPARSER_H_

#include <string>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <memory>

class Rule;

class ArgsParser {

	bool quiet_;
	bool suppress_;
	bool valid_;
	bool structure_;
	bool interactive_;
	bool hideerrors_;

	std::string wordtype_;
	std::string infinitive_;
	std::string psuedo_infinitive_;
	std::string conjugation_;
	std::string filename_;
	std::string vowel_;
	std::string stem_;
	std::string negate_;
	std::string person_;
	std::string error_;
	std::string datatype_;


	std::set<char> flags_;
	std::vector<std::string> inputs_;
	std::map<char,std::string> messages_;
	std::vector<std::shared_ptr<Rule>> rules_;

	void CreateRules();
	// void ExtractFlags(int argc,const char *argv[] );
	void ExtractFlags(const std::vector<std::string> &args);
	void ExtractFlags(const std::string &args );
	void ProcessFlags();
	void Display(){
		if(hideerrors_){
			return;
		}
		if(!Quiet() || (!valid_&& error_.size()>0) ){

			std::cout << "Spanish Verb Conjugator" << std::endl;
			if(!valid_ ){
				std::cout << "Invalid input : " << error_ << std::endl;
			}
			// review this in the morning
			for(auto v: flags_){
				std::cout << v << messages_[v] << std::endl;
			}
		}
	}

	void PopulateMessages()
	{
		messages_['v']=" : Verbose";
		messages_['p']=" : Suppress pronoun";
		messages_['n']=" : Negate verb conjugation";
		messages_['i']=" : Individual conjugation";
		messages_['f']=" : Input filename to expand";
		messages_['t']=" : Word type, e.g. noun, verb";
		messages_['c']=" : Vowel change in stem";
		messages_['s']=" : Stem overwrite for first person singular";
		messages_['j']=" : Conjugation override for file-sourced entities";
		messages_['r']=" : Output structure rather than phrase";
		messages_['d']=" : Datatype: Word or Verb";
		messages_['w']=" : Hide warnings and errors";
	}

	bool ValidateInput();

public:
	ArgsParser();
	// ArgsParser(int argc,const char *argv[]);
	ArgsParser(const std::vector<std::string> &args);
	ArgsParser(const std::string &args);
	virtual ~ArgsParser();

	std::string Wordtype(){return wordtype_;}
	std::string Infinitive(){return infinitive_;}
	std::string PsuedoInfinitive(){return psuedo_infinitive_;}
	std::string Conjugation() const {return conjugation_;}
	void Conjugation(std::string conjugation){conjugation_=conjugation;}
	std::string Filename() const {return filename_;}
	std::string Vowel(){return vowel_;}
	std::string Stem(){return stem_;}
	std::string Negate() const {return negate_;}
	void Negate(std::string value){negate_=value;}
	std::string Person(){return person_;}
	std::string Datatype() const {return datatype_;}

	bool Interactive(){return interactive_;}
	bool Quiet(){return quiet_;}
	bool Suppress(){return suppress_;}
	bool Valid(){return valid_;}
	bool Structure() const {return structure_;}
	void Structure(bool value){structure_=value;}
};

#endif /* ARGSPARSER_H_ */
