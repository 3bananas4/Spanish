/*
 * main.cpp
 *
 *  Created on: 4 Dec 2019
 *      Author: james
 */
#include <vector>
#include <string>
#include <sstream>
#include <memory>

#include "Selector.h"
#include "ArgsParser.h"
#include "Content.h"
#include "Parser.h"
#include "Feeder.h"

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

const std::string app="DummyApp";
const std::string tener="tener";
const std::string tengo="tengo";
const std::string venir="venir";
const std::string vengo="vengo";
const std::string recordar = "recordar";

void testInfWithVec(const std::vector<std::string> &params,const std::string & testval,bool truth)
{
	ArgsParser ap(params);
	if(truth){
		REQUIRE(ap.Infinitive().compare(testval)==0);
	}
	else {
		REQUIRE(ap.Infinitive().compare(testval)!=0);
	}
}

void testInfWithStr(const std::string &initializer,const std::string & testval,bool truth)
{
	ArgsParser ap(initializer);
	if(truth){
		REQUIRE(ap.Infinitive().compare(testval)==0);
	}
	else {
		REQUIRE(ap.Infinitive().compare(testval)!=0);
	}
}

void testConjWithVec(const std::vector<std::string> &params,const std::string &testval,bool truth)
{
	std::shared_ptr<ArgsParser> ap = std::make_shared<ArgsParser>(params);
	std::string ss;
	Selector sel(params,[&ss](const std::string& output)->int{ss=output;return 0;});
	if(truth){
		sel.conjugateVerb(ap);
		REQUIRE(ss.compare(testval)==0);
	}
}

void testConjWithStr(const std::string &initializer,const std::string &testval,bool truth)
{
	std::shared_ptr<ArgsParser> ap = std::make_shared<ArgsParser>(initializer);
	std::string ss;
	Selector sel({"-w"},[&ss](const std::string& output)->int{ss=output;return 0;});
	if(truth){
		sel.conjugateVerb(ap);
		REQUIRE(ss.compare(testval)==0);
	}
}

TEST_CASE( "infinitives with vector", "" ) {
	SECTION("simple infinitive"){testInfWithVec({app,"-i","comer","1"},"comer",true);}
	SECTION("check against garbage value"){testInfWithVec({app,"-i","comer","1"},"garbage",false);}
	SECTION("infinitive with vowel change"){testInfWithVec({app,"-ic","entender","1","e_ie"},"entender",true);}

	// i want the app to detect if the verb isn't correctly defined as ar,er or ir ( allowing for se )
}

TEST_CASE( "infinitives with string", "" ) {
	SECTION("simple infinitive"){testInfWithStr("-i comer 1","comer",true);}
	SECTION("include app name to test error"){testInfWithStr(app+" -iw comer 1","comer",false);}
	SECTION("check against garbage value"){testInfWithStr("-i comer 1","garbage",false);}
	SECTION("infinitive with vowel change"){testInfWithStr("-ic entender 1 e_ie","entender",true);}

}

TEST_CASE( "ar verb","" ) {
	SECTION("p0"){testConjWithVec({app,"-ic",recordar,"0","o_ue"},recordar,true);}
	SECTION("p1"){testConjWithVec({app,"-ic",recordar,"1","o_ue"},"yo recuerdo",true);}
	SECTION("p2"){testConjWithVec({app,"-ic",recordar,"2","o_ue"},"tú recuerdas",true);}
	SECTION("p3"){testConjWithVec({app,"-ic",recordar,"3","o_ue"},"él recuerda",true);}
	SECTION("p4"){testConjWithVec({app,"-ic",recordar,"4","o_ue"},"nosotros recordamos",true);}
	SECTION("p5"){testConjWithVec({app,"-ic",recordar,"5","o_ue"},"vosotros recordáis",true);}
	SECTION("p6"){testConjWithVec({app,"-ic",recordar,"6","o_ue"},"ellos recuerdan",true);}

	SECTION("p1 str"){testConjWithStr("-ic recordar 1 o_ue","yo recuerdo",true);}
	SECTION("p6 str"){testConjWithStr("-ic recordar 6 o_ue","ellos recuerdan",true);}
}

TEST_CASE( "er verb","" ) {
	SECTION("p0"){testConjWithVec({app,"-isc",tener,"0","e_ie",tengo},tener,true);}
	SECTION("p1"){testConjWithVec({app,"-isc",tener,"1","e_ie",tengo},"yo "+tengo,true);}
	SECTION("p2"){testConjWithVec({app,"-isc",tener,"2","e_ie",tengo},"tú tienes",true);}
	SECTION("p3"){testConjWithVec({app,"-isc",tener,"3","e_ie",tengo},"él tiene",true);}
	SECTION("p4"){testConjWithVec({app,"-isc",tener,"4","e_ie",tengo},"nosotros tenemos",true);}
	SECTION("p5"){testConjWithVec({app,"-isc",tener,"5","e_ie",tengo},"vosotros teneis",true);}
	SECTION("p6"){testConjWithVec({app,"-isc",tener,"6","e_ie",tengo},"ellos tienen",true);}
}

TEST_CASE( "ir verb","" ) {
	SECTION("p0"){testConjWithVec({app,"-isc",venir,"0","e_ie",vengo},venir,true);}
	SECTION("p1"){testConjWithVec({app,"-isc",venir,"1","e_ie",vengo},"yo "+vengo,true);}
	SECTION("p2"){testConjWithVec({app,"-isc",venir,"2","e_ie",vengo},"tú vienes",true);}
	SECTION("p3"){testConjWithVec({app,"-isc",venir,"3","e_ie",vengo},"él viene",true);}
	SECTION("p4"){testConjWithVec({app,"-isc",venir,"4","e_ie",vengo},"nosotros venimos",true);}
	SECTION("p5"){testConjWithVec({app,"-isc",venir,"5","e_ie",vengo},"vosotros venis",true);}
	SECTION("p6"){testConjWithVec({app,"-isc",venir,"6","e_ie",vengo},"ellos vienen",true);}
}

TEST_CASE( "negated","" ) {
	SECTION("p1"){testConjWithVec({app,"-in","hablar","1"},"yo no hablo",true);}
	SECTION("p3"){testConjWithVec({app,"-in","hablar","3"},"él no habla",true);}
}

TEST_CASE( "reflexive","" ) {
	SECTION("p1"){testConjWithVec({app,"-i","bañarse","1"},"yo me baño",true);}
	SECTION("p3"){testConjWithVec({app,"-i","bañarse","3"},"él se baña",true);}
}

TEST_CASE( "negated reflexive","" ) {
	SECTION("p1"){testConjWithVec({app,"-in","bañarse","1"},"yo no me baño",true);}
	SECTION("p3"){testConjWithVec({app,"-in","bañarse","3"},"él no se baña",true);}
}

TEST_CASE( "suppressed","" ) {
	SECTION("p1"){testConjWithVec({app,"-ip","hablar","1"},"hablo",true);}
	SECTION("p3"){testConjWithVec({app,"-ip","hablar","3"},"habla",true);}
}

TEST_CASE( "suppressed negated","" ) {
	SECTION("p1"){testConjWithVec({app,"-inp","hablar","1"},"no hablo",true);}
	SECTION("p3"){testConjWithVec({app,"-inp","hablar","3"},"no habla",true);}
}

TEST_CASE( "suppressed negated reflexive","" ) {
	SECTION("p1"){testConjWithVec({app,"-inp","bañarse","1"},"no me baño",true);}
	SECTION("p3"){testConjWithVec({app,"-inp","bañarse","3"},"no se baña",true);}
}

TEST_CASE( "suppressed negated reflexive vowelchange","" ) {
	SECTION("p1"){testConjWithVec({app,"-icnp","sentarse","1","e_ie"},"no me siento",true);}
	SECTION("p3"){testConjWithVec({app,"-icnp","sentarse","3","e_ie"},"no se sienta",true);}
	SECTION("p5"){testConjWithVec({app,"-icnp","sentarse","5","e_ie"},"no os sentáis",true);}
}

TEST_CASE( "suppressed negated reflexive stemchange","" ) {
	SECTION("p1"){testConjWithVec({app,"-isnp","reponerse","1","repongo"},"no me repongo",true);}
	SECTION("p3"){testConjWithVec({app,"-isnp","reponerse","3","repongo"},"no se repone",true);}
	SECTION("p4"){testConjWithVec({app,"-isnp","reponerse","4","repongo"},"no nos reponemos",true);}
}

TEST_CASE( "suppressed negated reflexive stemchange string input","" ) {
	SECTION("p1"){testConjWithStr("-isnp reponerse 1 repongo","no me repongo",true);}
	SECTION("p3"){testConjWithStr("-isnp reponerse 3 repongo","no se repone",true);}
	SECTION("p4"){testConjWithStr("-isnp reponerse 4 repongo","no nos reponemos",true);}
}

void testReadFromFile(const std::vector<std::string> &filecontents,const std::string &wordType,const std::string &target)
{
	std::stringstream ss;
	Selector sel({"dummyapp","-fwd","dummyfile",wordType},[&ss](const std::string &output)->int{ ss<<"["<<output<<"]";return 0;});

	auto parser = [](const std::string& s){return Parser::Process(s);};

	auto loader = [&parser,&filecontents](std::shared_ptr<Content> content){
		for(auto s : filecontents){content->insert(s,parser);}
	};
	sel.conjugate(loader);

	REQUIRE(ss.str().compare(target)==0);
}

TEST_CASE("Test reading from file"){
	SECTION("Verbs"){
		std::vector<std::string> v = {"{speak:\"-i hablar 1\"}","{sing:\"-i cantar 1\"}"};
		testReadFromFile(v,"Verbs","[sing : cantar][speak : hablar]");
	}
	SECTION("Full Word List"){
		std::vector<std::string> v = {
			"{\"foreign\" : \"hola\",\"english\" : \"hello\",\"wordtype\" : \"expr\"}",
			"{\"foreign\" : \"la botella\",\"english\" : \"bottle\",\"wordtype\" : \"noun\"}"};
		testReadFromFile(v,"","[English: bottle, Spanish: la botella, Wordtype: noun][English: hello, Spanish: hola, Wordtype: expr]");
	}

}

TEST_CASE("Test the lookup app"){
	Feeder feeder({"dummyapp","dummyfile","make","1"});
	auto parser = [](const std::string& s)->STRVEC{return LookupParser::Process(s);};
	feeder.addEntry("{make:\"-is hacer 1 hago\"}",parser);
	feeder.addEntry("{sing:\"-i cantar 1\"}",parser);

	SECTION("Feed"){
		REQUIRE(feeder.feedPipe().compare("-is hacer 1 hago")==0);
	}
	SECTION("Dictionary Size"){
		REQUIRE(feeder.Content().size()==2);
	}

	Feeder feeder2({"dummyapp","dummyfile","sing","2"});
	feeder2.addEntry("{make:\"-is hacer 1 hago\"}",parser);
	feeder2.addEntry("{sing:\"-i cantar 1\"}",parser);

	SECTION("Conjugation"){
		REQUIRE(feeder2.feedPipe().compare("-i cantar 2")==0);
	}
}
