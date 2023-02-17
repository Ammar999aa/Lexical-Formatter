#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>

#include "global.h"
#include "Word.h"
#include "Verb.h"
#include "Noun.h"
#include "Adjective.h"
#include "Adverb.h"
#include "id.h"

using namespace std;

ThetaCell::ThetaCell(int role, int phrase)
	: element(role), type(phrase) 
{}

Verb::Verb(ID identity, string name, string meaning, list<ThetaCell> thetaGrid, string note)
	: Word(identity, name, meaning, VERB, note), grid(thetaGrid), childNoun(), childAdj(), childAdv(), derivedId()
{}

Verb::Verb(ID identity, string name, string meaning, list<ThetaCell> thetaGrid)
	: Word(identity, name, meaning, VERB), grid(thetaGrid), childNoun(), childAdj(), childAdv()
{}

std::list<ThetaCell> Verb::getGrid() const
{
    return grid;
}

std::list<Noun*> Verb::getChildNoun() const
{
    return childNoun;
}

std::list<Adjective*> Verb::getChildAdj() const
{
    return childAdj;
}

std::list<Adverb*> Verb::getChildAdv() const
{
    return childAdv;
}

vector<ID> Verb::getDerivationID() const
{
    return derivedId;
}

void Verb::addDerived(ID id)
{
    derivedId.push_back(id);
}

void Verb::removeDerivation(ID id)
{
    for (int i = 0; i < derivedId.size(); i++)
    {
        if (derivedId[i] == id)
        {
            derivedId.erase(derivedId.begin() + i);
        }
    }
}

string getRandomRoot(list<string>& corpus)
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
        list<string>::iterator corpusIt;
		for (corpusIt = corpus.begin(); corpusIt != corpus.end(); corpusIt++)
			if (*corpusIt == word)
				validWord = false;

		if (validWord)
			return word;
	}
}

void addVerbs(list<Verb>& library, list<string>& corpus, ID_Manager& manager)
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
            list<string>::iterator corpusIt;
            for (corpusIt = corpus.begin(); corpusIt != corpus.end(); corpusIt++)
                if (*corpusIt == name)
                    validWord = false;

			if (!validWord)
			{
				clearScreen();
				cout << "input " << name << " already exists" << endl;
				continue;
			}
		}

		cout << "input the translation" << endl;
		cin >> meaning;
		cout << "Choose one of the builtin theta grids" << endl
			<< "(1) eat     (2) want    (3) go      (4) put     (5) sleep   " << endl;
		cin >> role;

		vector<list<ThetaCell>> grids = { gridEat, gridWant, gridGo, gridPut, gridSleep };

        ID id = manager.generateID(VERB, nullptr, name);
        Verb finalVerb(id, name, meaning, grids[role - 1]);
		library.push_back(finalVerb);
        corpus.push_back(name);
        
        //list<ThetaCell>::iterator thetaIt;
        //for (thetaIt = library.end()->getGrid().begin(); thetaIt = )
		clearScreen();
	}
}

void deleteVerb(list<Verb>::iterator it, string name, vector<ID> derivationID, list<Verb>& verbLibrary, list<Noun>& nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary, list<string>& corpus, ID_Manager& manager)
{
    verbLibrary.erase(it);
    corpus.remove(name);
    
    if (derivationID.size() != 0)
    {
        cout << "delete derivations?" << endl;
        cout << "y for yes, n for no." << endl;
        
        string choice;
        cin >> choice;
        if (choice == "y")
        {
            for (int i = 0; i < derivationID.size(); i++)
            {
                if (derivationID[i].getCategory() == NOUN)
                {
                    for (list<Noun>::iterator nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
                    {
                        // do they have the same id?
                        if (nounIt->getId() == derivationID[i])
                        {
                            corpus.remove(nounIt->getSelf());
                            nounLibrary.erase(nounIt);
                            break;
                        }
                    }
                }
                if (derivationID[i].getCategory() == ADJ)
                {
                    for (list<Adjective>::iterator adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
                    {
                        // do they have the same id?
                        if (adjIt->getId() == derivationID[i])
                        {
                            corpus.remove(adjIt->getSelf());
                            adjLibrary.erase(adjIt);
                            break;
                        }
                    }
                }
                if (derivationID[i].getCategory() == ADV)
                {
                    for (list<Adverb>::iterator advIt = advLibrary.begin(); advIt != advLibrary.end(); advIt++)
                    {
                        // do they have the same id?
                        if (advIt->getId() == derivationID[i])
                        {
                            corpus.remove(advIt->getSelf());
                            advLibrary.erase(advIt);
                            break;
                        }
                    }
                }
            }
            cout << "derivations deleted" << endl;
        }
    }
}
