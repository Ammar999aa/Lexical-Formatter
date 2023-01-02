#ifndef WORD
#define WORD


#include <iostream>
#include <string>
#include <cstdlib>
#include "global.h"

class Word
{
public:
	Word(int identity, string name, string meaning, string note)
		: id(identity), self(name), translation(meaning), note(note) {}
	Word(int identity, string name, string meaning)
		: id(identity), self(name), translation(meaning)
	{
		note = "";
	}

	int id;
	string self;
	string translation;
	string note;
};


#endif