#include <iostream>
#include <string>
#include <vector>
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

Word::Word(int identity, string name, string meaning, int cat, string note)
	: id(identity), self(name), translation(meaning), category(cat), note(note) 
{}

Word::Word(int identity, string name, string meaning, int cat)
	: id(identity), self(name), translation(meaning), category(cat)
{
	note = "";
}