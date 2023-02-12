#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <time.h>
#include <math.h>

#include "global.h"
#include "Word.h"
#include "Verb.h"
#include "Noun.h"
#include "Adjective.h"
#include "Adverb.h"

using namespace std;

Word::Word(ID identity, string name, string meaning, int cat, string note)
	: id(identity), self(name), translation(meaning), category(cat), note(note) 
{}

Word::Word(ID identity, string name, string meaning, int cat)
	: id(identity), self(name), translation(meaning), category(cat)
{
	note = "";
}

// accessors
ID Word::getId() const
{
    return id;
}

string Word::getSelf() const
{
    return self;
}

string Word::getTranslation() const
{
    return translation;
}

string Word::getNote() const
{
    return note;
}

int Word::getCategory() const
{
    return category;
}
