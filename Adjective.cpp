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

void addAdjectives(vector<Adjective>&library, vector<Noun>&nounLibrary, vector<string>&corpus)
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
			for (int i = 0; i < nounLibrary.size(); i++)
			{
				if (nounLibrary[i].self == name)
				{
					nounFound = true;
					root = &nounLibrary[i];
				}
			}

			//seach by translation (if name not found)
			if (!nounFound)
			{
				for (int i = 0; i < nounLibrary.size(); i++)
				{
					if (nounLibrary[i].translation == name)
					{
						nounFound = true;
						root = &nounLibrary[i];
					}
				}
			}

			if (!nounFound)
			{
				clearScreen();
				cout << "noun not found. Check spelling or add root";
				continue;
			}

			cout << "Noun found: \"" << root->self << "\", meaning \"" << root->translation << "\". ID: " << root->id << endl;
			cout << "choose affix: " << endl;
			cout << "(1) " << root->self << "es  (2) " << root->self << "no  " << endl;

			int choice;
			cin >> choice;

			switch (choice)
			{
			case 1:
				name = root->self + "es";
				break;
			case 2:
				name = root->self + "no";
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

			id = root->id + 1;
			Adjective adj(id, name, meaning, root);
			library.push_back(adj);
			corpus.push_back(name);

			if (root->root->childAdj == " ")
			{
				root->root->childAdj = adj.self;
			}

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

			library.push_back(Adjective(1, name, meaning, nullptr));
			corpus.push_back(name);

			clearScreen();
			cout << "adjective created!" << endl;

		}
	}
}