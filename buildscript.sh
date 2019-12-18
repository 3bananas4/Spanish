# create the lib folder and move into the shared source folder
mkdir lib build -p
cd shared/src

# build the object file
g++ -c Parser.cpp
g++ -c FileReader.cpp
g++ -c Component.cpp

# create the archive
ar crf ../../lib/libshared.a Parser.o FileReader.o Component.o

# build the index using ranlib
ranlib ../../lib/libshared.a

cd ../../LookupVerb/src/content
g++ -c Feeder.cpp

ar crf ../../../lib/liblookup.a Feeder.o

ranlib ../../../lib/liblookup.a

cd ../main/
g++ -c LookupVerb.cpp -I./ -I../../../shared/src -I../content

g++ -o ../../../build/LookupVerb LookupVerb.o -L../../../lib -llookup -lshared
##################################################
cd ../../../spanish1/src/content/
g++ -c ArgsParser.cpp
g++ -c Content.cpp
g++ -c Rule.cpp
g++ -c VerbBase.cpp -I../../../shared/src
g++ -c Selector.cpp -I../../../shared/src
g++ -c Word.cpp

ar crf ../../../lib/libconjugator.a ../../../shared/src/Component.o ArgsParser.o Content.o Rule.o VerbBase.o Selector.o Word.o

ranlib ../../../lib/libconjugator.a

cd ../main/
g++ -c spanish1.cpp -I../../../shared/src -I../content -I./

g++ -o ../../../build/conjugator spanish1.o -I../../../shared/src -I../content -I./ -L../../../lib -lshared -lconjugator 

##################################################
cd ../../../TestSuite/src
g++ -c main.cpp  -I../../shared/src -I../../spanish1/src/content -I../../LookupVerb/src/content -I./

g++ -o ../../build/testsuite main.o -L../../lib -lshared -lconjugator -llookup


