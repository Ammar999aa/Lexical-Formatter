#ifndef FORMATH
#define FORMATH

#include <iostream>
#include <string>
#include <list>
#include <list>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "global.h"
#include "Word.h"
#include "Verb.h"
#include "Noun.h"
#include "Adjective.h"
#include "Adverb.h"
#include "id.h"

void printVerb(std::list<Verb>& verbLibrary, std::list<Noun>& nounLibrary, std::list<Adjective>& adjLibrary, std::list<Adverb>& advLibrary, std::list<Verb>::iterator verbIt);

void printNoun(std::list<Noun>::iterator nounIt);

void printAdj(std::list<Adjective>::iterator adjIt);

void printAdv(std::list<Adverb>::iterator advIt);

void formatAlphabetically(std::list<Verb>& verbLibrary, std::list<Noun>& nounLibrary, std::list<Adjective>& adjLibrary, std::list<Adverb>& advLibrary, std::list<std::string> corpus, ID_Manager& manager);

void format(std::list<Verb>& verbLibrary, std::list<Noun>& nounLibrary, std::list<Adjective>& adjLibrary, std::list<Adverb>& advLibrary, std::list<std::string>& corpus, ID_Manager& manager);

#endif
