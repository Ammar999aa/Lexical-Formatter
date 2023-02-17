#ifndef ADJECTIVEH
#define ADJECTIVEH

#include "Word.h"
#include "Noun.h"
#include "id.h"

class Adjective : public Word
{
public:
	Adjective(ID identity, std::string name, std::string meaning, Noun* root, std::string note);
	Adjective(ID identity, std::string name, std::string meaning, Noun* root);
    
    //accessors
    Noun* getRoot() const;
    
private:
	Noun* root;
};

void addAdjectives(std::list<Adjective>& library, std::list<Noun>& nounLibrary, std::list<std::string>& corpus, ID_Manager& manager);

void deleteAdjective(std::list<Adjective>::iterator it, std::string name, std::list<Adjective>& library, std::list<Verb>& verbLibrary, std::list<std::string>& corpus, ID_Manager& manager);


#endif
