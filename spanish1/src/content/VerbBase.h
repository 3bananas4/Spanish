/*
 * VerbBase.h
 *
 *  Created on: 25 Nov 2019
 *      Author: james
 */

#ifndef VERBBASE_H_
#define VERBBASE_H_

#include <string>
#include <vector>
#include <memory>

class Component;

class VerbBase {


protected:
	std::string infinitive_;
	std::string pronoun_;
	std::vector<std::shared_ptr<Component>> structure_;

public:
	enum Conjugation {Inf,FirstSing,SecondSing,ThirdSing,FirstPlu,SecondPlu,ThirdPlu} ;
	VerbBase();
	VerbBase(const std::string& infinitive);
	virtual ~VerbBase();

	virtual std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);

	static bool isReflexive(const std::string& infinitive){
		return infinitive.substr(infinitive.length()-2).compare("se")==0;
	}

	static inline std::string verbType(const std::string& infinitive){
		return isReflexive(infinitive)?infinitive.substr(infinitive.length()-4,2):infinitive.substr(infinitive.length()-2);
	}

	static inline std::string stem(const std::string& infinitive){
		return isReflexive(infinitive)?infinitive.substr(0,infinitive.length()-4):infinitive.substr(0,infinitive.length()-2);
	}

	const virtual std::string& Infinitive(){return infinitive_;}

private:
	std::string Pronoun(Conjugation conjugation);
};

class VerbDecorator : public VerbBase
{
protected:
	std::shared_ptr<VerbBase> decoratedVerb_;

public:
	VerbDecorator (std::shared_ptr<VerbBase> decoratedVerb):
		decoratedVerb_(decoratedVerb) {}
	~VerbDecorator(){}

	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class ConjDecorator : public VerbDecorator
{
	std::string verbsuffix(Conjugation conjugation);
public:
	ConjDecorator (std::shared_ptr<VerbBase> decoratedVerb): VerbDecorator(decoratedVerb) {}
	~ConjDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class ReflexiveDecorator : public VerbDecorator
{
	std::string Pronoun(Conjugation conjugation);
public:
	ReflexiveDecorator (std::shared_ptr<VerbBase> decoratedVerb): VerbDecorator(decoratedVerb) {}
	~ReflexiveDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class VowelDecorator : public VerbDecorator
{
	std::string vowel_;
	std::string Modify(Conjugation conjugation,const std::string &basestring);
public:
	VowelDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string vowel): VerbDecorator(decoratedVerb),vowel_(vowel) {}
	~VowelDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class StemDecorator : public VerbDecorator
{
	std::string stem_;
	std::string Modify(Conjugation conjugation,const std::string & basestring);
public:
	StemDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string stem): VerbDecorator(decoratedVerb),stem_(stem) {}
	~StemDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class NegateDecorator : public VerbDecorator
{
	std::string negate_;
public:
	NegateDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string negate): VerbDecorator(decoratedVerb),negate_(negate) {}
	~NegateDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class PersonDecorator : public VerbDecorator
{
	std::string person_;
public:
	PersonDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string person): VerbDecorator(decoratedVerb),person_(person) {}
	~PersonDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class SuppressDecorator : public VerbDecorator
{
	bool suppress_;
public:
	SuppressDecorator (std::shared_ptr<VerbBase> decoratedVerb,bool suppress): VerbDecorator(decoratedVerb),suppress_(suppress) {}
	~SuppressDecorator(){}

	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};



#endif /* VERBBASE_H_ */
