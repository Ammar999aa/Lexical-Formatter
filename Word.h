#ifndef WORDH
#define WORDH

#include <iostream>
#include <string>
#include <cstdlib>
#include "global.h"

class Word
{
public:
	Word(int identity, std::string name, std::string meaning, int cat, std::string note);
	Word(int identity, std::string name, std::string meaning, int cat);
    
    //acessors
    int getId() const;
    std::string getSelf() const;
    std::string getTranslation() const;
    std::string getNote() const;
    int getCategory() const;

private:
	int id;
	std::string self;
	std::string translation;
	std::string note;
	int category;
};

#endif
