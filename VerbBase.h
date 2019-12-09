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

	//virtual std::string conjugate(Conjugation conjugation);
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

	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class ARVerbDecorator : public VerbDecorator
{
	std::string verbsuffix(Conjugation conjugation);
public:
	ARVerbDecorator (std::shared_ptr<VerbBase> decoratedVerb): VerbDecorator(decoratedVerb) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class ERVerbDecorator : public VerbDecorator
{
	std::string verbsuffix(Conjugation conjugation);
public:
	ERVerbDecorator (std::shared_ptr<VerbBase> decoratedVerb): VerbDecorator(decoratedVerb) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class IRVerbDecorator : public VerbDecorator
{
	std::string verbsuffix(Conjugation conjugation);
public:
	IRVerbDecorator (std::shared_ptr<VerbBase> decoratedVerb): VerbDecorator(decoratedVerb) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class ReflexiveDecorator : public VerbDecorator
{
	std::string Pronoun(Conjugation conjugation);
public:
	ReflexiveDecorator (std::shared_ptr<VerbBase> decoratedVerb): VerbDecorator(decoratedVerb) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class VowelDecorator : public VerbDecorator
{
	std::string vowel_;
	std::string Modify(Conjugation conjugation,/*size_t pos,*/const std::string &basestring);
public:
	VowelDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string vowel): VerbDecorator(decoratedVerb),vowel_(vowel) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class StemDecorator : public VerbDecorator
{
	std::string stem_;
	std::string Modify(Conjugation conjugation,/*size_t pos,*/const std::string & basestring);
public:
	StemDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string stem): VerbDecorator(decoratedVerb),stem_(stem) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class NegateDecorator : public VerbDecorator
{
	std::string negate_;
public:
	NegateDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string negate): VerbDecorator(decoratedVerb),negate_(negate) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class PersonDecorator : public VerbDecorator
{
	std::string person_;
public:
	PersonDecorator (std::shared_ptr<VerbBase> decoratedVerb,std::string person): VerbDecorator(decoratedVerb),person_(person) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};

class SuppressDecorator : public VerbDecorator
{
	bool suppress_;
public:
	SuppressDecorator (std::shared_ptr<VerbBase> decoratedVerb,bool suppress): VerbDecorator(decoratedVerb),suppress_(suppress) {}

	//std::string conjugate(Conjugation conjugation);
	std::vector<std::shared_ptr<Component>>& conjugate_struct(Conjugation conjugation);
	const virtual std::string& Infinitive(){return decoratedVerb_->Infinitive();}
};



#endif /* VERBBASE_H_ */
