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
#include "id.h"

using namespace std;

Adverb::Adverb(ID identity, string name, string meaning, Adjective* root, string note)
	: Word(identity, name, meaning, ADV, note), root(root)
{}

Adverb::Adverb(ID identity, string name, string meaning, Adjective* root)
	: Word(identity, name, meaning, ADV), root(root)
{}

Adjective* Adverb::getRoot() const
{
    return root;
}

void addAdverbs(list<Adverb>& library, list<Adjective>& adjLibrary, list<string>& corpus, ID_Manager& manager)
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
                if (adjIt->getSelf() == name)
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
                    if (adjIt->getTranslation() == name)
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

			cout << "Adjective found: \"" << root->getSelf() << "\", meaning \"" << root->getTranslation() << "\". ID: " << root->getId().display() << endl;
			cout << "choose affix: " << endl;
			cout << "(1) " << root->getSelf() << "ang  (2) " << root->getSelf() << "ju  " << endl;

			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
				name = root->getSelf() + "ang";
				break;
			case 2:
				name = root->getSelf() + "ju";
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

            ID id = manager.generateID(ADV, root->getRoot()->getRoot(), name);
			Adverb adv(id, name, meaning, root);
			library.push_back(adv);
			corpus.push_back(name);

            root->getRoot()->getRoot()->getChildAdv().push_back(&adv);

			clearScreen();
			cout << name << " added! ID: " << id.display() << endl;

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

            ID id = manager.generateID(ADV, nullptr, name);
			library.push_back(Adverb(id, name, meaning, nullptr));
			corpus.push_back(name);

			clearScreen();
			cout << "adverb created!" << endl;

		}
	}
}

void deleteAdverb(list<Adverb>::iterator it, list<Adverb>& library, list<Verb>& verbLibrary, list<string>& corpus, ID_Manager& manager)
{
    //it->getRoot()->getRoot()->getRoot()->deleteDerived...
    library.erase(it);
    corpus.remove(it->getSelf());
}
