#ifndef WORDH
#define WORDH


#include <iostream>
#include <string>
#include <cstdlib>
#include "global.h"

class Word
{
public:
	Word(int identity, string name, string meaning, int cat, string note)
		: id(identity), self(name), translation(meaning), category(cat), note(note) {}
	Word(int identity, string name, string meaning, int cat)
		: id(identity), self(name), translation(meaning), category(cat)
	{
		note = "";
	}

	int id;
	string self;
	string translation;
	string note;
	int category;
};


#endif