#ifndef ADVERBH
#define ADVERBH

#include "Word.h"
#include "Adjective.h"


class Adverb : public Word
{
public:
	Adverb(ID identity, std::string name, std::string meaning, Adjective* root, std::string note);
	Adverb(ID identity, std::string name, std::string meaning, Adjective* root);
    
    // accessors
    Adjective* getRoot() const;
    
private:
	Adjective* root;
};

void addAdverbs(std::list<Adverb>& library, std::list<Adjective>& adjLibrary, std::list<std::string>& corpus, ID_Manager& manager);

void deleteAdverb(std::list<Adverb>::iterator it, std::string name, std::list<Adverb>& library, std::list<Verb>& verbLibrary, std::list<std::string>& corpus, ID_Manager& manager);


#endif
