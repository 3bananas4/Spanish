/*
 * VerbBase.cpp
 *
 *  Created on: 25 Nov 2019
 *      Author: james
 */

#include "VerbBase.h"
#include "Component.h"

using namespace std;

VerbBase::VerbBase() {
	// TODO Auto-generated constructor stub

}

VerbBase::VerbBase(const std::string& infinitive) : infinitive_(infinitive){

}

VerbBase::~VerbBase() {
	// TODO Auto-generated destructor stub
}

string VerbBase::Pronoun(Conjugation conjugation)
{
	vector<string> pronouns = {"","yo","tú","él","nosotros","vosotros","ellos"};
	return pronouns[static_cast<unsigned>(conjugation)];
}

std::vector<std::shared_ptr<Component>>& VerbBase :: conjugate_struct(Conjugation conjugation)
{
	structure_={
				//make_shared<Component>("Pronoun",Pronoun(conjugation)),
				make_shared<Component>((conjugation==Conjugation::Inf)?"Infinitive":"Verb",conjugation==Conjugation::Inf?infinitive_:VerbBase::stem(infinitive_))};
	if(conjugation!=Conjugation::Inf){
		structure_.insert(structure_.begin(),make_shared<Component>("Pronoun",Pronoun(conjugation)));
	}

	return structure_;
}

string ConjDecorator::verbsuffix(VerbBase::Conjugation conjugation)
{
	vector<string> suffix = {"","o","as","a","amos","áis","an"};
	string vbtype = VerbBase::verbType(Infinitive());
	if(vbtype.compare("er")==0){
		suffix = {"","o","es","e","emos","eis","en"};
	}
	else if(vbtype.compare("ir")==0){
		suffix = {"","o","es","e","imos","is","en"};
	}
	return suffix[static_cast<unsigned>(conjugation)];
}

std::vector<std::shared_ptr<Component>>& ConjDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	v.back()->Value( v.back()->Value()+verbsuffix(conjugation));

	return v;
}
/*
string ARVerbDecorator::verbsuffix(VerbBase::Conjugation conjugation)
{
	vector<string> suffix = {"","o","as","a","amos","áis","an"};
	return suffix[static_cast<unsigned>(conjugation)];
}

std::vector<std::shared_ptr<Component>>& ARVerbDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	v.back()->Value( v.back()->Value()+verbsuffix(conjugation));

	return v;
}

string ERVerbDecorator::verbsuffix(VerbBase::Conjugation conjugation)
{
	vector<string> suffix = {"","o","es","e","emos","eis","en"};
	return suffix[static_cast<unsigned>(conjugation)];
}

std::vector<std::shared_ptr<Component>>& ERVerbDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	v.back()->Value( v.back()->Value()+verbsuffix(conjugation));

	return v;
}

string IRVerbDecorator::verbsuffix(VerbBase::Conjugation conjugation)
{
	vector<string> suffix = {"","o","es","e","imos","is","en"};
	return suffix[static_cast<unsigned>(conjugation)];
}

std::vector<std::shared_ptr<Component>>& IRVerbDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	v.back()->Value( v.back()->Value()+verbsuffix(conjugation));

	return v;
}
*/
string ReflexiveDecorator::Pronoun(Conjugation conjugation)
{
	vector<string> pronoun = {"","me","te","se","nos","os","se"};
	return pronoun[static_cast<unsigned>(conjugation)];
}

std::vector<std::shared_ptr<Component>>& ReflexiveDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	if(VerbBase::isReflexive( Infinitive() ) && (conjugation!=Conjugation::Inf)){
		v.insert(v.begin()+1,make_shared<Component>("Reflexive",Pronoun(conjugation)));
	}

	return v;
}

string VowelDecorator::Modify(Conjugation conjugation,const string &basestring)
{
	size_t s1 = vowel_.find('_');
	string s = basestring;
	if(s1!=string::npos){
		string old = vowel_.substr(0,s1);
		string rep = vowel_.substr(s1+1);

		string verbform = basestring;
		size_t s2 = verbform.find_last_of(old);
		if(s2!=string::npos){
			verbform = verbform.substr(0,s2) + rep + verbform.substr(s2+1);
		}
		// recompose
		switch(conjugation){
		case Conjugation::FirstSing :
		case Conjugation::SecondSing :
		case Conjugation::ThirdSing :
		case Conjugation::ThirdPlu :
			s = verbform;
		}
	}
	return s;
}

std::vector<std::shared_ptr<Component>>& VowelDecorator::conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	if(! vowel_.empty() && (conjugation!=Conjugation::Inf)){
		v.back()->Value(Modify(conjugation,v.back()->Value()));
	}

	return v;
}

string StemDecorator::Modify(Conjugation conjugation,const string & basestring)
{
	return conjugation==Conjugation::FirstSing?stem_:basestring;
}

std::vector<std::shared_ptr<Component>>& StemDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	if(!stem_.empty() && (conjugation!=Conjugation::Inf)){
		v.back()->Value(Modify(conjugation,/*0,*/v.back()->Value()));
	}
	return v;
}

std::vector<std::shared_ptr<Component>>& NegateDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	if(!negate_.empty() && (conjugation!=Conjugation::Inf)){
		v.insert(v.begin()+1,make_shared<Component>("Negative",negate_));
	}
	return v;
}

std::vector<std::shared_ptr<Component>>& PersonDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	if(person_.size()>0 && (conjugation==Conjugation::ThirdSing || conjugation==Conjugation::ThirdPlu)){
		if((conjugation==Conjugation::ThirdSing && (person_=="usted" || person_=="ella")) ||
					   (conjugation==Conjugation::ThirdPlu && (person_=="ustedes" || person_=="ellas"))){
			v[0]->Value(person_);
		}
	}
	return v;
}

std::vector<std::shared_ptr<Component>>& SuppressDecorator :: conjugate_struct(Conjugation conjugation)
{
	auto &v = decoratedVerb_->conjugate_struct(conjugation);
	if(suppress_ && (conjugation!=Conjugation::Inf)){
		v[0]->Value("");
	}
	return v;
}
