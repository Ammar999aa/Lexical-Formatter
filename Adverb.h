#ifndef ADVERBH
#define ADVERBH

#include "Word.h"
#include "Adjective.h"

class Adverb : public Word
{
public:
	Adverb(int identity, std::string name, std::string meaning, Adjective* root, std::string note);
	Adverb(int identity, std::string name, std::string meaning, Adjective* root);

	Adjective* root;
};

void addAdverbs(std::list<Adverb>& library, std::list<Adjective>& adjLibrary, std::list<std::string>& corpus);

#endif