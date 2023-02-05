#ifndef NOUNH
#define NOUNH

#include "Word.h"
#include "Verb.h"

class Noun : public Word
{
public:
	Noun(int identity, std::string name, std::string meaning, Verb* root, std::string note);
	Noun(int identity, std::string name, std::string meaning, Verb* root);

	Verb* root;
};

void addNouns(std::list<Noun>& library, std::list<Verb>& verbLibrary, std::list<std::string>& corpus);

#endif
