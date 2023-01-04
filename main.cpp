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

void clearScreen()
{
	cout << "\033[2J\033[1;1H";
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

string getRandomRoot(vector<string> &corpus)
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

void addVerbs(vector<Verb>& library, vector<string> &corpus)
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