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

void clearScreen()
{
	cout << "\033[2J\033[1;1H";
}

void setSeed()
{
	cout << "To set a seed, you can input it here. Otherwise, input 0" << endl;
	int seed;
	cin >> seed;

	if (seed == 0)
		srand(time(0));
	else
		srand(seed);
}