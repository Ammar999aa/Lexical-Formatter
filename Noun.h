#ifndef NOUNH
#define NOUNH

#include "Verb.h";
#include "Word.h";

class Noun : public Word
{
public:
	Noun(int identity, std::string name, std::string meaning, Verb* root, std::string note);
	Noun(int identity, std::string name, std::string meaning, Verb* root);

	Verb* root;
};

void addNouns(std::vector<Noun>& library, std::vector<Verb>& verbLibrary, std::vector<std::string>& corpus);

#endif NOUNH