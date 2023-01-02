#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>

#include "global.h"
#include "Verb.h"

using namespace std;

void clearScreen()
{
	cout << "\033[2J\033[1;1H";
}

string getRandomRoot(vector<Verb> &illegalWords)
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
		for (int i = 0; i < illegalWords.size(); i++)
			if (illegalWords[i].self == word)
				validWord = false;

		if (validWord)
			return word;
	}
}

void format(vector<Verb> & dictionary)
{
	string throwaway;
	while (1)
	{

		vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
		vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };

		for (int i = 0; i < dictionary.size(); i++)
		{
		cout << dictionary[i].self << " - " << dictionary[i].translation << endl;
		// traverse through the grid of the verb and print each emelent along with its type
		cout << "	 | ";
		for (int j = 0; j < dictionary[i].grid.size(); j++)
		{
		cout << elements[dictionary[i].grid[j].element] << " (" << types[dictionary[i].grid[j].type] << ") | ";
		}
		cout << endl << endl;
		}

		cout << "To quit, submit 'done' or 'd' " << endl;
		cin >> throwaway;
		if (throwaway == "done" || throwaway == "d")
			break;
		clearScreen();
	}
}

void addVerbs(vector<Verb> & library)
{
	cout << "You can now add verbs. Once finished, submit 'done' " << endl;

	string name = ".";
	string meaning;
	int role;

	while (1)
	{
		cout << "add your verb: 'r' for a random name, 'done' to finish" << endl;
		cin >> name;
		if (name == "done")
		{
			clearScreen();
			break;
		}
		else if (name == "r")
		{
			name = getRandomRoot(library);
			cout << "The random verb you got is " << name << "! " << endl;
		}
		else
		{
			bool validWord = true;
			for (int i = 0; i < library.size(); i++)
				if (library[i].self == name)
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

		vector<vector<ThetaCell>> grids = { gridEat, gridWant, gridGo, gridPut, gridSleep };

		library.push_back(Verb(library.size(), name, meaning, grids[role - 1]));

		clearScreen();
	}
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

void generateCode(vector<Verb>& library)
{
	cout << "vector<library> library = { " << endl;
	for (int i = 0; i < library.size() - 1; i++)
	{
		cout << "Verb(" << library[i].id << ", \"" << library[i].self << "\", \"" << library[i].translation << "\", " << "gridEat" << ")";
		cout << ", " << endl;
	}
	cout << "Verb(" << library[library.size() - 1].id << ", \"" << library[library.size() - 1].self << "\", \"" << library[library.size() - 1].translation << "\", " << "gridEat" << ")";
	cout << " };" << endl;

}

int main()
{
	srand(time(0));
	Verb done(1, "ken", "do", gridEat);
	Verb eat(1, "rom", "eat", gridEat);
	vector<Verb> library = { done, eat };

	cout << "Welcome to the Lexical Formatter, a tool that helps create and format all the words in your Conlang!" << endl;
	cout << "=========================" << endl;
	
	while (1)
	{
		cout << "You are now in the main menu, select an option to start: " << endl;
		cout << "(0) Set Seed  (1) Add Verbs  (2) Format     (3) Generate Code  " << endl;

		int choice;
		cin >> choice;

		clearScreen();
		switch (choice)
		{
		case 0:
			setSeed();
			break;
		case 1:
			addVerbs(library);
			break;
		case 2:
			format(library);
			break;
		case 3:
			generateCode(library);
			break;
		}
		clearScreen();
	}

}