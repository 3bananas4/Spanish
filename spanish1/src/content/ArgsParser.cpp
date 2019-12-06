/*
 * ArgsParser.cpp
 *
 *  Created on: 26 Nov 2019
 *      Author: james
 */

#include <set>
#include <memory>
#include <algorithm>
#include "ArgsParser.h"
#include "Rule.h"
using namespace std;

typedef vector<Rule::RuleType> rulevec;

ArgsParser::ArgsParser()
: quiet_(true),
  suppress_(false),
  valid_(true),
  structure_(false),
  interactive_(false),
  hideerrors_(false),
  wordtype_("All")
{

}
/*
ArgsParser::ArgsParser(int argc,const char *argv[])
: quiet_(true),
  suppress_(false),
  valid_(true),
  structure_(false),
  interactive_(false),
  wordtype_("All"){
	// TODO Auto-generated constructor stub
	ExtractFlags(argc,argv);
	valid_ = ValidateInput();
	ProcessFlags();
	PopulateMessages();
	Display();
}
*/
ArgsParser::ArgsParser(const std::vector<std::string> &args)
: quiet_(true),
  suppress_(false),
  valid_(true),
  structure_(false),
  interactive_(false),
  hideerrors_(false),
  wordtype_("All"){
	ExtractFlags(args);
	valid_ = ValidateInput();
	ProcessFlags();
	PopulateMessages();
	Display();
}

ArgsParser::ArgsParser(const std::string &args)
: quiet_(true),
  suppress_(false),
  valid_(true),
  structure_(false),
  interactive_(false),
  hideerrors_(false),
  wordtype_("All")
{
	ExtractFlags(args);
	valid_ = ValidateInput();
	ProcessFlags();
	PopulateMessages();
	Display();
}

ArgsParser::~ArgsParser() {
	// TODO Auto-generated destructor stub
}

void ArgsParser::ExtractFlags(const std::string &args )
{
	char ch = ' ';
	size_t start=0;
	size_t end=args.find_first_of(ch);

	std::vector<std::string> output;
	while (end <= std::string::npos)
	{
		std::string s = args.substr(start, end-start);
		//trim(s);
		output.emplace_back(s);
		if (end == std::string::npos)
			break;

		start=end+1;
		end = args.find_first_of(ch, start);
	}
	output.insert(output.begin(),"DummyApp");
	ExtractFlags(output);
}
/*
void ArgsParser::ExtractFlags(int argc,const char *argv[] )
{
	for(int i=0;i<argc;++i){
		string arg(argv[i]);
		if( argv[i][0]== '-'){
			if(arg.length()>2){
				for(size_t ch=1;ch<arg.length();++ch){
					flags_.insert(arg[ch]);
				}
			}
			else if(arg.length()>1){
				flags_.insert(arg[1]);
			}
		}
		else {
			inputs_.push_back(arg);
		}
	}
}
*/
void ArgsParser::ExtractFlags(const std::vector<std::string> &args )
{
	for(unsigned i=0;i<args.size();++i){
		string arg(args[i]);
		if( arg[0]== '-'){
			if(arg.length()>2){
				for(size_t ch=1;ch<arg.length();++ch){
					flags_.insert(arg[ch]);
				}
			}
			else if(arg.length()>1){
				flags_.insert(arg[1]);
			}
		}
		else {
			inputs_.push_back(arg);
		}
	}
}

void ArgsParser::CreateRules()
{
	rules_.push_back(make_shared<FlagRule>('f','i',rulevec{Rule::RuleType::EitherNotBoth}));
	rules_.push_back(make_shared<FlagRule>('t','f',rulevec{Rule::RuleType::IfFirstSecond}));
	rules_.push_back(make_shared<FlagRule>('j','f',rulevec{Rule::RuleType::IfFirstSecond}));
	rules_.push_back(make_shared<FlagRule>('d','f',rulevec{Rule::RuleType::IfFirstSecond}));
	rules_.push_back(make_shared<FlagRule>('c','i',rulevec{Rule::RuleType::IfFirstSecond}));
	rules_.push_back(make_shared<FlagRule>('s','i',rulevec{Rule::RuleType::IfFirstSecond}));
	rules_.push_back(make_shared<FlagRule>('p','i',rulevec{Rule::RuleType::IfFirstSecond}));
	//rules_.push_back(make_shared<FlagRule>('n','i',rulevec{Rule::RuleType::IfFirstSecond}));

	rules_.push_back(make_shared<OptionRule>('f',rulevec{Rule::RuleType::OptionCountExceedsOne}));
	rules_.push_back(make_shared<OptionRule>('t',rulevec{Rule::RuleType::OptionCountExceedsTwo}));
	rules_.push_back(make_shared<OptionRule>('j',rulevec{Rule::RuleType::OptionCountExceedsTwo}));
	rules_.push_back(make_shared<OptionRule>('d',rulevec{Rule::RuleType::OptionCountExceedsTwo}));
	rules_.push_back(make_shared<OptionRule>('i',rulevec{Rule::RuleType::OptionCountExceedsTwo,Rule::RuleType::OptionThreeIsNumeral}));
	rules_.push_back(make_shared<OptionRule>('c',rulevec{Rule::RuleType::OptionCountExceedsThree,Rule::RuleType::OptionContainsUnderscore}));
	rules_.push_back(make_shared<OptionRule>('s',rulevec{Rule::RuleType::OptionCountExceedsThree,Rule::RuleType::OptionCountExceedsFourIfC}));
}

bool ArgsParser::ValidateInput()
{
	CreateRules();
	bool rv(true);

	for(auto r : rules_) {
		rv &=r->test(flags_,inputs_);
		if(!rv){
			error_=r->error();
			break;
		}
	}

	return rv;
}

void ArgsParser::ProcessFlags()
{
	vector<string> inputs = inputs_;
	set<string> changes = {"e_i","e_ie","o_ue","u_ue"};
	set<string> sing_pron = {"ella","usted"};
	set<string> plu_pron = {"ellas","ustedes"};

	// validate before we get to this
	if(flags_.find('v')!=flags_.end()){
		quiet_=false;
	}
	if(flags_.find('n')!=flags_.end()){
		negate_="no";
	}
	if(flags_.find('p')!=flags_.end()){
		suppress_=true;
	}
	if(flags_.find('r')!=flags_.end()){
		structure_=true;
	}
	if(flags_.find('w')!=flags_.end()){
		hideerrors_=true;
	}

	if(flags_.find('c')!=flags_.end()){
		vector<string> v1(10);
		auto v2 = inputs;
		sort (v2.begin(),v2.end());

		auto it = set_intersection(v2.begin(),v2.end(),changes.begin(),changes.end(),v1.begin());
		v1.resize(it-v1.begin());
		if(v1.size()==1){
			vowel_ = v1[0];
		}
	}
	if(flags_.find('t')!=flags_.end()){
		wordtype_ = inputs[inputs.size()-1];
	}
	if(flags_.find('f')!=flags_.end()){
		filename_ = inputs[1];
	}
	if(flags_.find('d')!=flags_.end()){
		datatype_ = inputs[2];
	}
	if(flags_.find('j')!=flags_.end()){
		conjugation_ = inputs[inputs.size()-1]; // might this conflict with 'w'
		// run with this for now but need to work out how to differentiate
		// between j and w inputs if both exist
	}
	if(flags_.find('i')!=flags_.end()){
		size_t pos = inputs[1].find("/",0);

		infinitive_ = pos==string::npos?inputs[1]:inputs[1].substr(0,pos);
		psuedo_infinitive_ = pos==string::npos?inputs[1]:inputs[1].substr(pos+1);
		conjugation_ = inputs[2];

		if(atoi(conjugation_.c_str())>0){
			vector<string> v1(10);
			auto v2 = inputs;
			sort (v2.begin(),v2.end());
			bool sing = atoi(conjugation_.c_str())<4?true:false;
			auto it = set_intersection(
					v2.begin(),
					v2.end(),
					sing?sing_pron.begin():plu_pron.begin(),
					sing?sing_pron.end():plu_pron.end(),
					v1.begin());
			v1.resize(it-v1.begin());
			if(v1.size()==1){
				person_ = v1[0];
			}
		}
	}
	if(flags_.find('s')!=flags_.end()){
		vector<string> v = inputs;
		v.erase(v.begin());
		vector<string> used = {infinitive_,psuedo_infinitive_,conjugation_,person_,vowel_};
		for(auto val : used){
			auto it = find(v.begin(),v.end(),val);
			if(it!=v.end()){
				v.erase(it);
			}
		}
		if(v.size()>0){
			stem_ =v.back();
		}
	}
}
