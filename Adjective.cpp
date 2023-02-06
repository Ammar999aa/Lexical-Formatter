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

Adjective::Adjective(int identity, string name, string meaning, Noun* root, string note)
	: Word(identity, name, meaning, ADJ, note), root(root)
{}

Adjective::Adjective(int identity, string name, string meaning, Noun* root)
	: Word(identity, name, meaning, ADJ), root(root)
{}

Noun* Adjective::getRoot() const
{
    return root;
}

void addAdjectives(list<Adjective>&library, list<Noun>&nounLibrary, list<string>&corpus)
{
	cout << "You can now add adjectives. Once finished, submit 'done' " << endl;

	while (1)
	{
		string name = ".";
		string meaning;
		int id;
		Noun* root = nullptr;

		cout << "add your adjectives: 'r' for a noun-derived adjective, 'done' or 'd' to finish" << endl;
		cin >> name;
		if (name == "done" || name == "d")
		{
			clearScreen();
			break;
		}
		else if (name == "r")
		{
			cout << "input the name of the noun, or the translation of the noun" << endl;
			cin >> name;

			// search by name
			bool nounFound = false;
            list<Noun>::iterator nounIt;
            for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
            {
                if (nounIt->getSelf() == name)
                {
                    nounFound = true;
                    root = &(*nounIt);
                }
            }

			//seach by translation (if name not found)
			if (!nounFound)
			{
                for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
                {
                    if (nounIt->getSelf() == meaning)
                    {
                        nounFound = true;
                        root = &(*nounIt);
                    }
                }
			}

			if (!nounFound)
			{
				clearScreen();
				cout << "noun not found. Check spelling or add root";
				continue;
			}

			cout << "Noun found: \"" << root->getSelf() << "\", meaning \"" << root->getTranslation() << "\". ID: " << root->getId() << endl;
			cout << "choose affix: " << endl;
			cout << "(1) " << root->getSelf() << "es  (2) " << root->getSelf() << "no  " << endl;

			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
				name = root->getSelf() + "es";
				break;
			case 2:
				name = root->getSelf() + "no";
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

			id = root->getId() + 1;
			Adjective adj(id, name, meaning, root);
			library.push_back(adj);
			corpus.push_back(name);

            root->getRoot()->getChildAdj().push_back(&adj);

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

			library.push_back(Adjective(1, name, meaning, nullptr));
			corpus.push_back(name);

			clearScreen();
			cout << "adjective created!" << endl;

		}
	}
}
