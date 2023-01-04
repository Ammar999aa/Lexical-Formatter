#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <math.h>

#include "global.h"
#include "Verb.h"
#include "Noun.h"

using namespace std;

void format(vector<Verb> & verbLibrary, vector<Noun> & nounLibrary, vector<string> & corpus)
{
	string throwaway;
	while (1)
	{

		vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
		vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
		vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };

		for (int i = 0; i < verbLibrary.size(); i++)
		{
			cout << verbLibrary[i].self << " - " << verbLibrary[i].translation << " (" << categories[verbLibrary[i].category] << ")" << endl;
			// traverse through the grid of the verb and print each emelent along with its type
			cout << "	 | ";

			if (verbLibrary[i].category == VERB)
			{
				for (int j = 0; j < verbLibrary[i].grid.size(); j++)
				{
					cout << elements[verbLibrary[i].grid[j].element] << " (" << types[verbLibrary[i].grid[j].type] << ") | ";
				}
			}
			
			cout << endl << endl;
		}
		for (int i = 0; i < nounLibrary.size(); i++)
		{
			cout << nounLibrary[i].self << " - " << nounLibrary[i].translation << " (" << categories[nounLibrary[i].category] << ")" << endl;
			
			if (nounLibrary[i].root != nullptr)
				cout << "	from: " << nounLibrary[i].root->self << endl;

			cout << endl;
		}

		cout << "To quit, submit 'done' or 'd' " << endl;
		cin >> throwaway;
		if (throwaway == "done" || throwaway == "d")
			break;
		clearScreen();
	}
}

void generateDelim(vector<Verb>& library)
{
	
	string throwaway;
	while (1)
	{
		for (int i = 0; i < library.size(); i++)
		{
			cout << library[i].category << ";" << library[i].id << ";" << library[i].self << ";" << library[i].translation << ";" << library[i].note << ";";

			if (library[i].category == VERB)
			{
				cout << library[i].grid.size() << ";";

				for (int j = 0; j < library[i].grid.size(); j++)
				{
					cout << library[i].grid[j].element << ";" << library[i].grid[j].type << ";";
				}
			}
			cout << "#";
		}

		cout << endl << endl << "To quit, submit 'done' or 'd' " << endl;
		cin >> throwaway;
		if (throwaway == "done" || throwaway == "d")
			break;
		clearScreen();
	}

}

vector<Verb> parseDelim(string text)
{
	vector<Verb> words = {};
	
	int i = 0;
	while (i < text.size())
	{
		int identity;
		int cat;
		string name = "";
		string meaning = "";
		string note = "";
		
		string temp_cat = "";
		while (text[i] != ';')
		{
			temp_cat += text[i];
			i++;
		}

		if (temp_cat.size() != 1)
		{
			cout << "category error" << endl;
			break;
		}

		cat = temp_cat[0] - 48;

		//cerr << "category " << i << ": " << cat << endl;
		i++;

		string temp_id = "";
		while (text[i] != ';')
		{
			temp_id += text[i];
			i++;
		}

		identity = 0;
		for (int k = temp_id.size() - 1; k > -1; k--)
		{
			identity += temp_id[k] * pow(10, (temp_id.size() - k - 1)) - 48;
		}

		// cerr << "id " << i << ": " << identity << endl;
		i++;
		while (text[i] != ';')
		{
			name += text[i];
			i++;
		}

		//cerr << "name " << i << ": " << name << endl;
		i++;
		while (text[i] != ';')
		{
			meaning += text[i];
			i++;
		}

		//cerr << "meaning " << i << ": " << meaning << endl;
		i++;
		while (text[i] != ';')
		{
			note += text[i];
		}

		//cerr << "notes " << i << ": " << note << endl;
		i++;
		if (cat == VERB)
		{
			vector<int> roles = {};
			vector<int> phrases = {};
			
			int gridSize = text[i] - 48;
			i += 2;

			for (int n = 0; n < gridSize; n++)
			{
				//cerr << text[i] << endl;
				roles.push_back(text[i] - 48);
				i += 2;
				//cerr << text[i] << endl;
				phrases.push_back(text[i] - 48);
				i += 2;
			}

			i++;
			
			if (cat == VERB)
			{
				vector<ThetaCell> thetaGrid = {};
				for (int p = 0; p < gridSize; p++)
				{
					thetaGrid.push_back(ThetaCell(roles[p], phrases[p]));
				}

				for (int h = 0; h < thetaGrid.size(); h++)
				{
					//cerr << "(" << thetaGrid[h].element << ", " << thetaGrid[h].type << ")" << endl;
				}

				words.push_back(Verb(identity, name, meaning, thetaGrid));
			}
		}
	}

	return words;
}

void uploadWords(vector<Verb>& library)
{
	string throwaway;
	while (1)
	{
		string text;
		cin >> text;

		vector<Verb> words = parseDelim(text);

		for (int i = 0; i < words.size(); i++)
		{
			library.push_back(words[i]);
		}

		//clearScreen();
		cout << "Words Successfully Added!" << endl << "Submit 'd' to exit" << endl;
		cin >> throwaway;
		if (throwaway == "done" || throwaway == "d")
			break;
		clearScreen();
	}
}

int main()
{
	srand(time(0));
	Verb done(1, "ken", "do", gridEat);
	Verb eat(1, "rom", "eat", gridEat);
	vector<Verb> verbLibrary = { };
	vector<Noun> nounLibrary = { };
	vector<Word> wordLibrary = { };
	vector<string> corpus = { };

	cout << "Welcome to the Lexical Formatter, a tool that helps create and format all the words in your Conlang!" << endl;
	cout << "=========================" << endl;
	
	while (1)
	{
		cout << "You are now in the main menu, select an option to start: " << endl;
		cout << "(0) Set Seed  (1) Add Verbs  (2) Add Nouns " << endl;
		cout << "(3) Format  (4) Generate Delim  (5) Upload Delim  " << endl;

		int choice;
		cin >> choice;

		clearScreen();
		switch (choice)
		{
		case 0:
			setSeed();
			break;
		case 1:
			addVerbs(verbLibrary, corpus);
			break;
		case 2:
			addNouns(nounLibrary, verbLibrary, corpus);
			break;
		case 3:
			format(verbLibrary, nounLibrary, corpus);
			break;
		case 4:
			generateDelim(verbLibrary);
			break;
		case 5:
			uploadWords(verbLibrary);
		}
		clearScreen();
	}

}