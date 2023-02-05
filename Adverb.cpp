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

Adverb::Adverb(int identity, string name, string meaning, Adjective* root, string note)
	: Word(identity, name, meaning, ADV, note), root(root)
{}

Adverb::Adverb(int identity, string name, string meaning, Adjective* root)
	: Word(identity, name, meaning, ADV), root(root)
{}

void addAdverbs(list<Adverb>& library, list<Adjective>& adjLibrary, list<string>& corpus)
{
	cout << "You can now add adjverbs. Once finished, submit 'done' " << endl;

	while (1)
	{
		string name = ".";
		string meaning;
		int id;
		Adjective* root = nullptr;

		cout << "add your adverbs: 'r' for a adjectve-derived adverb, 'done' or 'd' to finish" << endl;
		cin >> name;
		if (name == "done" || name == "d")
		{
			clearScreen();
			break;
		}
		else if (name == "r")
		{
			cout << "input the name of the adjective, or the translation of the adjective" << endl;
			cin >> name;

            // search by name
            bool adjFound = false;
            list<Adjective>::iterator adjIt;
            for (adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
            {
                if (adjIt->self == name)
                {
                    adjFound = true;
                    root = &(*adjIt);
                }
            }

            //seach by translation (if name not found)
            if (!adjFound)
            {
                for (adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
                {
                    if (adjIt->self == meaning)
                    {
                        adjFound = true;
                        root = &(*adjIt);
                    }
                }
            }

			if (!adjFound)
			{
				clearScreen();
				cout << "adjective not found. Check spelling or add root";
				continue;
			}

			cout << "Adjective found: \"" << root->self << "\", meaning \"" << root->translation << "\". ID: " << root->id << endl;
			cout << "choose affix: " << endl;
			cout << "(1) " << root->self << "ang  (2) " << root->self << "ju  " << endl;

			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
				name = root->self + "ang";
				break;
			case 2:
				name = root->self + "ju";
				break;
			}

            bool validWord = true;
            list<string>::iterator corpusIt;
            for (corpusIt = corpus.begin(); corpusIt != corpus.end(); corpusIt++)
            {
                if (*corpusIt == name)
                {
                    validWord = false;
                }
            }

			if (validWord)
			{
				corpus.push_back(name);
			}
			else
			{
				clearScreen();
				cout << "word already exists" << endl;
				continue;
			}

			cout << "Submit the meaning of " << name << endl;
			cin >> meaning;

			id = root->id + 1;
			Adverb adv(id, name, meaning, root);
			library.push_back(adv);
			corpus.push_back(name);

            root->root->root->childAdv.push_back(&adv);

			clearScreen();
			cout << name << " added! ID: " << id << endl;

		}
		else
		{
            bool validWord = true;
            list<string>::iterator corpusIt;
            for (corpusIt = corpus.begin(); corpusIt != corpus.end(); corpusIt++)
            {
                if (*corpusIt == name)
                {
                    validWord = false;
                }
            }
            
			if (validWord)
			{
				corpus.push_back(name);
			}
			else
			{
				clearScreen();
				cout << "word already exists" << endl;
				continue;
			}

			cout << "enter meaning for " << name << endl;
			cin >> meaning;

			library.push_back(Adverb(1, name, meaning, nullptr));
			corpus.push_back(name);

			clearScreen();
			cout << "adverb created!" << endl;

		}
	}


}
