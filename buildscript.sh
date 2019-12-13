# create the lib folder and move into the shared source folder
mkdir lib build -p
cd shared/src

# build the object file
g++ -c Parser.cpp
g++ -c FileReader.cpp

# create the archive
ar crf ../../lib/libshared.a Parser.o FileReader.o

# build the index using ranlib
ranlib ../../lib/libshared.a

cd ../../LookupVerb/src
g++ -c InfContent.cpp
g++ -c LookupVerb.cpp -I./ -I../../shared/src

g++ -o ../../build/LookupVerb InfContent.o LookupVerb.o -I./ -I../../shared/src -L../../lib -lshared 
##################################################
cd ../../spanish1/src/content/
g++ -c ArgsParser.cpp
g++ -c Content.cpp
g++ -c Rule.cpp
g++ -c VerbBase.cpp
g++ -c Component.cpp
g++ -c Selector.cpp
g++ -c Word.cpp

ar crf ../../../lib/libconjugator.a ArgsParser.o Content.o Rule.o VerbBase.o Component.o Selector.o Word.o

ranlib ../../../lib/libconjugator.a

cd ../main/
g++ -c spanish1.cpp -I../../../shared/src -I../content -I./

g++ -o ../../../build/conjugator spanish1.o -I../../../shared/src -I../content -I./ -L../../../lib -lshared -lconjugator 

##################################################
cd ../../../TestSuite/src
g++ -c main.cpp  -I../../shared/src -I../../spanish1/src/content -I./

g++ -o ../../build/testsuite main.o -I../../shared/src -I../../spanish1/content -I./ -L../../lib -lshared -lconjugator 



