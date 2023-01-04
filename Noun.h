#ifndef NOUNH
#define NOUNH

#include "Verb.h";
#include "Word.h";

class Noun : public Word
{
public:
	Noun(int identity, string name, string meaning, Verb* root , string note)
		: Word(identity, name, meaning, NOUN, note), root(root) {}
	Noun(int identity, string name, string meaning, Verb* root)
		: Word(identity, name, meaning, NOUN), root(root) {}

	Verb* root;
};


#endif NOUNH