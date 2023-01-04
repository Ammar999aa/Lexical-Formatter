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

Adjective::Adjective(int identity, string name, string meaning, Noun* root, string note)
	: Word(identity, name, meaning, ADJ, note), root(root)
{}

Adjective::Adjective(int identity, string name, string meaning, Noun* root)
	: Word(identity, name, meaning, ADJ), root(root)
{}

Noun* root;