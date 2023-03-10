#ifndef NOUNH
#define NOUNH

#include "Word.h"
#include "Verb.h"

class Noun : public Word
{
public:
	Noun(ID identity, std::string name, std::string meaning, Verb* root, std::string note);
	Noun(ID identity, std::string name, std::string meaning, Verb* root);
    // accessors
    Verb* getRoot() const;
private:
	Verb* root;
};

void addNouns(std::list<Noun>& library, std::list<Verb>& verbLibrary, std::list<std::string>& corpus, ID_Manager& manager);

void deleteNoun(std::list<Noun>::iterator it, std::string name, std::list<Noun>& library, std::list<Verb>& verbLibrary, std::list<std::string>& corpus, ID_Manager& manager);

#endif
