/*
 * Feeder.h
 *
 *  Created on: 15 Dec 2019
 *      Author: james
 */

#ifndef FEEDER_H_
#define FEEDER_H_

#include <vector>
#include <functional>
#include <sstream>
#include <string>
#include <map>

typedef std::vector<std::string> STRVEC;
typedef std::function<STRVEC(const std::string&)> f_svec_s;
typedef std::function<STRVEC(const std::string &,char)> f_svec_s_c;

class Feeder {

	STRVEC args_;
	std::map<std::string,STRVEC> dict_;

	std::string composeCommand(const STRVEC &filecommands,const std::string &conjugation);
	void runPrompt(bool showPrompt,std::function<bool(const std::string&)> process);
	int  openApp(const std::string &command);
	bool processLine(
			const std::string &lineInput,
			std::function<STRVEC(const std::string &,char)> parse,
			std::function<std::string(const STRVEC&)> compose);

public:
	Feeder();
	Feeder(const std::vector<std::string> &args);
	virtual ~Feeder();

	void addEntry(const std::string &entry,std::function<STRVEC(const std::string& s)> parser);
	std::string feedPipe();
	void interactive(bool showPrompt,std::function<STRVEC(const std::string&,char)> parser);

	std::map<std::string,STRVEC> const & Content() const {return this->dict_;}

};

#endif /* FEEDER_H_ */
