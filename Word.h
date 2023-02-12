#ifndef WORDH
#define WORDH

#include <iostream>
#include <string>
#include <cstdlib>
#include "global.h"
#include "id.h"

class Word
{
public:
	Word(ID identity, std::string name, std::string meaning, int cat, std::string note);
	Word(ID identity, std::string name, std::string meaning, int cat);
    
    //acessors
    ID getId() const;
    std::string getSelf() const;
    std::string getTranslation() const;
    std::string getNote() const;
    int getCategory() const;

private:
	ID id;
	std::string self;
	std::string translation;
	std::string note;
	int category;
};

#endif
