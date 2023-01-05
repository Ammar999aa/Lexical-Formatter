#ifndef ADJECTIVEH
#define ADJECTIVEH

#include "Word.h"
#include "Noun.h"

class Adjective : public Word
{
public:
	Adjective(int identity, std::string name, std::string meaning, Noun* root, std::string note);
	Adjective(int identity, std::string name, std::string meaning, Noun* root);

	Noun* root;
};

void addAdjectives(std::vector<Adjective>& library, std::vector<Noun>& nounLibrary, std::vector<std::string>& corpus);

#endif