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

Noun::Noun(int identity, string name, string meaning, Verb* root, string note)
	: Word(identity, name, meaning, NOUN, note), root(root) 
{}

Noun::Noun(int identity, string name, string meaning, Verb* root)
	: Word(identity, name, meaning, NOUN), root(root) 
{}

void appendNoun(list<Noun> library, Noun &noun, Verb *root)
{
	library.push_back(noun);
	//Add this noun as a child to the verb
	//root->childNouns.push_back(&library[library.size() - 1]);
}

void addNouns(list<Noun>& library, list<Verb>& verbLibrary, list<string>& corpus)
{
	cout << "You can now add nouns. Once finished, submit 'done' " << endl;

	while (1)
	{
		string name = ".";
		string meaning;
		int id;
		Verb* root = nullptr;

		cout << "add your noun: 'r' for a root-derived noun, 'done' or 'd' to finish" << endl;
		cin >> name;
		if (name == "done" || name == "d")
		{
			clearScreen();
			break;
		}
		else if (name == "r")
		{
			cout << "input the name of the root, or the translation of the root" << endl;
			cin >> name;

			// search by name
			bool verbFound = false;
            list<Verb>::iterator verbIt;
            for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
            {
                if (verbIt->self == name)
                {
                    verbFound = true;
                    root = &(*verbIt);
                }
            }

			//seach by translation (if name not found)
            if (!verbFound)
            {
                for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
                {
                    if (verbIt->self == meaning)
                    {
                        verbFound = true;
                        root = &(*verbIt);
                    }
                }
            }

			if (!verbFound)
			{
				clearScreen();
				cout << "root not found. Check spelling or add root";
				continue;
			}

			cout << "Root found: \"" << root->self << "\", meaning \"" << root->translation << "\". ID: " << root->id << endl;
			cout << "choose affix: " << endl;
			cout << "(1) " << root->self << "al  (2) " << root->self << "ti  " << endl;

			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
				name = root->self + "al";
				break;
			case 2:
				name = root->self + "ti";
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

			id = (root->id * 100) + 1;
			Noun noun(id, name, meaning, root);
			library.push_back(noun);
			corpus.push_back(name);

			//Add this noun as a child to the verb
            cerr << &(noun.self) << endl;
            root->childNoun.push_back(&noun);

			/*
			for (int p = 0; p < 5; p++)
			{
				if (root->childNouns[p] != nullptr)
					cout << root->childNouns[p]->self << endl;
				else
					cout << "nullptr" << endl;
			}
			*/
			// root->childNouns.push_back(&noun);
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

			library.push_back(Noun(1, name, meaning, nullptr));
			corpus.push_back(name);

			clearScreen();
			cout << "noun created!" << endl;

		}
	}

}
