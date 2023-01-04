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

ThetaCell::ThetaCell(int role, int phrase)
	: element(role), type(phrase) 
{}

Verb::Verb(int identity, string name, string meaning, vector<ThetaCell> thetaGrid, string note)
	: Word(identity, name, meaning, VERB, note), grid(thetaGrid) 
{}

Verb::Verb(int identity, string name, string meaning, vector<ThetaCell> thetaGrid)
	: Word(identity, name, meaning, VERB), grid(thetaGrid) 
{}

string getRandomRoot(vector<string>& corpus)
{
	string word;

	while (1)
	{
		bool cluster = false;
		if ((rand() % 10) <= CLUSTER_CHANCE)
			cluster = true;

		int nucleus = rand() % 7;
		int coda = rand() % 16;

		if (!cluster)
		{
			int onset = rand() % 15;

			word = ONSET_NO_CLUSTER[onset] + NUCLEUS[nucleus] + CODA[coda];
		}
		else
		{
			int onset1 = rand() % 13;
			string onset2literal;

			switch (onset1)
			{
			case 6: //f
				onset2literal = F_CLUSTER[rand() % 3];
				break;
			case 3: //s
				onset2literal = S_CLUSTER[rand() % 8];
				break;
			case 12: //j
				onset2literal = J_CLUSTER[rand() % 7];
				break;
			case 11: //x
				onset2literal = X_CLUSTER[rand() % 4];
				break;
			default: //plosive or v
				onset2literal = PLOSIVE_V_CLUSTER[rand() % 2];
			}

			word = ONSET_CLUSTER[onset1] + onset2literal + NUCLEUS[nucleus] + CODA[coda];
		}

		bool validWord = true;
		for (int i = 0; i < corpus.size(); i++)
			if (corpus[i] == word)
				validWord = false;

		if (validWord)
			return word;
	}
}

void addVerbs(vector<Verb>& library, vector<string>& corpus)
{
	cout << "You can now add verbs. Once finished, submit 'done' " << endl;

	string name = ".";
	string meaning;
	int role;

	while (1)
	{
		cout << "add your verb: 'r' for a random name, 'done' or 'd' to finish" << endl;
		cin >> name;
		if (name == "done" || name == "d")
		{
			clearScreen();
			break;
		}
		else if (name == "r")
		{
			name = getRandomRoot(corpus);
			cout << "The random verb you got is " << name << "! " << endl;
		}
		else
		{
			bool validWord = true;
			for (int i = 0; i < corpus.size(); i++)
				if (corpus[i] == name)
					validWord = false;

			if (!validWord)
			{
				clearScreen();
				cout << "input " << name << " already exists" << endl;
				continue;
			}
			corpus.push_back(name);
		}

		cout << "input the translation" << endl;
		cin >> meaning;
		cout << "Choose one of the builtin theta grids" << endl
			<< "(1) eat     (2) want    (3) go      (4) put     (5) sleep   " << endl;
		cin >> role;

		vector<vector<ThetaCell>> grids = { gridEat, gridWant, gridGo, gridPut, gridSleep };

		library.push_back(Verb(library.size() + 1, name, meaning, grids[role - 1]));

		clearScreen();
	}
}