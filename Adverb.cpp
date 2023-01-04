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

Adverb::Adverb(int identity, string name, string meaning, Adjective* root, string note)
	: Word(identity, name, meaning, ADV, note), root(root)
{}

Adverb::Adverb(int identity, string name, string meaning, Adjective* root)
	: Word(identity, name, meaning, ADV), root(root)
{}