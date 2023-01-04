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

Noun::Noun(int identity, string name, string meaning, Verb* root, string note)
	: Word(identity, name, meaning, NOUN, note), root(root) 
{}

Noun::Noun(int identity, string name, string meaning, Verb* root)
	: Word(identity, name, meaning, NOUN), root(root) 
{}

void addNouns(vector<Noun>& library, vector<Verb>& verbLibrary, vector<string>& corpus)
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
			for (int i = 0; i < verbLibrary.size(); i++)
			{
				if (verbLibrary[i].self == name)
				{
					verbFound = true;
					root = &verbLibrary[i];
				}
			}

			//seach by translation (if name not found)
			if (!verbFound)
			{
				for (int i = 0; i < verbLibrary.size(); i++)
				{
					if (verbLibrary[i].translation == name)
					{
						verbFound = true;
						root = &verbLibrary[i];
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
			for (int j = 0; j < corpus.size(); j++)
			{
				if (corpus[j] == name)
				{
					!validWord;
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
			library.push_back(Noun(id, name, meaning, root));
			clearScreen();
			cout << name << " added! ID: " << id << endl;
		}
		else
		{

			bool validWord = true;
			for (int j = 0; j < corpus.size(); j++)
			{
				if (corpus[j] == name)
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

			clearScreen();
			cout << "noun created!" << endl;

		}
	}

}