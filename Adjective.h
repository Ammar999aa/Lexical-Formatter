#ifndef ADJECTIVEH
#define ADJECTIVEH

#include "Word.h"
#include "Noun.h"

class Adjective : public Word
{
public:
	Adjective(int identity, std::string name, std::string meaning, Noun* root, std::string note);
	Adjective(int identity, std::string name, std::string meaning, Noun* root);
    //accessors
    Noun* getRoot() const;
    
private:
	Noun* root;
};

void addAdjectives(std::list<Adjective>& library, std::list<Noun>& nounLibrary, std::list<std::string>& corpus);

#endif
