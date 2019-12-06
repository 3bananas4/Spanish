/*
 * Component.h
 *
 *  Created on: 29 Nov 2019
 *      Author: james
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_
#include <string>

class Component {

	std::string part_;
	std::string value_;
public:
	Component();
	Component(const std::string &part,const std::string &value);
	virtual ~Component();

	std::string Part(){return part_;}
	std::string Value(){return value_;}
	void Value(const std::string &value){value_=value;}
};

#endif /* COMPONENT_H_ */
