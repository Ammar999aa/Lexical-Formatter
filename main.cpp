#include <iostream>
#include <string>
#include <list>
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

using namespace std;

void format(list<Verb> & verbLibrary, list<Noun> & nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary, list<string> & corpus)
{
	string throwaway;
	while (1)
	{

		vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
		vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
		vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };
        
        list<Verb>::iterator verbIt;
		for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
		{
			cout << verbIt->self << " - " << verbIt->translation << " (" << categories[verbIt->category] << ")" << endl;
			// traverse through the grid of the verb and print each emelent along with its type
			cout << "	| ";
            
            list<ThetaCell>::iterator thetaIt;
			for (thetaIt = verbIt->grid.begin(); thetaIt != verbIt->grid.end(); thetaIt++)
			{
				cout << elements[thetaIt->element] << " (" << types[thetaIt->type] << ") | ";
			}
			
			cout << endl << "	derived:" << endl;
			if (verbIt->childNoun != " ")
			{
				cout << "	" << verbIt->childNoun << " (n)" << endl;
			}
			if (verbIt->childAdj != " ")
			{
				cout << "	" << verbIt->childAdj << " (Adj)" << endl;
			}
			if (verbIt->childAdv != " ")
			{
				cout << "	" << verbIt->childAdv << " (Adv)" << endl;
			}
			
			/*
			cout << endl << "	derived nouns:" << endl;
			for (int j = 0; j < 5; j++)
			{
				if (verbLibrary[i].childNouns[j] != nullptr)
				{
					cout << "	  " << verbLibrary[i].childNouns[0]->self << ": " << verbLibrary[i].childNouns[j]->translation << endl;
				}
			}
			*/
			/*
			if (verbLibrary[i].childNouns.size() > 0)
			{
				cout << endl << "	derived nouns:" << endl;

				// cout << "	  " << verbLibrary[i].childNouns[0]->self << endl;


				for (int g = 0; g < verbLibrary[i].childNouns.size(); g++)
				{
					if (verbLibrary[i].childNouns[g] != nullptr)
						cout << "	  " << verbLibrary[i].childNouns[g]->self << ": " << verbLibrary[i].childNouns[g]->translation << endl;
				}
			}
			*/

			cout << endl;
		}
        
        list<Noun>::iterator nounIt;
		for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
		{
			cout << nounIt->self << " - " << nounIt->translation << " (" << categories[nounIt->category] << ")" << endl;
			
			if (nounIt->root != nullptr)
				cout << "	from: " << nounIt->root->self << endl;

			cout << endl;
		}
        
        list<Adjective>::iterator adjIt;
		for (adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
		{
			cout << adjIt->self << " - " << adjIt->translation << " (" << categories[adjIt->category] << ")" << endl;

			if (adjIt->root != nullptr)
				cout << "	from: " << adjIt->root->self << endl;

			cout << endl;
		}
        
        list<Adverb>::iterator advIt;
        for (advIt = advLibrary.begin(); advIt != advLibrary.end(); advIt++)
        {
            cout << advIt->self << " - " << advIt->translation << " (" << categories[advIt->category] << ")" << endl;

            if (advIt->root != nullptr)
                cout << "    from: " << advIt->root->self << endl;

            cout << endl;
        }

		cout << "To quit, submit 'done' or 'd' " << endl;
		cin >> throwaway;
		if (throwaway == "done" || throwaway == "d")
			break;
		clearScreen();
	}
}

void generateDelim(list<Verb>& verbLibrary, list<Noun> &nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary)
{
}
void parseDelim(string& text, list<Verb>& verbLibrary, list<Noun>& nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary)
{
}
/*
void generateDelim(list<Verb>& verbLibrary, list<Noun> &nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary)
{
	
	string throwaway;
	while (1)
	{
		for (int i = 0; i < verbLibrary.size(); i++)
		{
			cout << verbLibrary[i].category << ";" << verbLibrary[i].id << ";" << verbLibrary[i].self << ";" << verbLibrary[i].translation << ";" << verbLibrary[i].note << ";";
			cout << verbLibrary[i].grid.size() << ";";

			for (int j = 0; j < verbLibrary[i].grid.size(); j++)
			{
				cout << verbLibrary[i].grid[j].element << ";" << verbLibrary[i].grid[j].type << ";";
			}
			cout << "#";
		}

		for (int i = 0; i < nounLibrary.size(); i++)
		{
			cout << nounLibrary[i].category << ";" << nounLibrary[i].id << ";" << nounLibrary[i].self << ";" << nounLibrary[i].translation << ";" << nounLibrary[i].note << ";";
			if (nounLibrary[i].root == nullptr)
				cout << "0;";
			else
				cout << nounLibrary[i].root->self << ";";
			cout << "#";
		}

		for (int i = 0; i < adjLibrary.size(); i++)
		{
			cout << adjLibrary[i].category << ";" << adjLibrary[i].id << ";" << adjLibrary[i].self << ";" << adjLibrary[i].translation << ";" << adjLibrary[i].note << ";";
			if (adjLibrary[i].root == nullptr)
				cout << "0;";
			else
				cout << adjLibrary[i].root->self << ";";
			cout << "#";
		}

		for (int i = 0; i < advLibrary.size(); i++)
		{
			cout << advLibrary[i].category << ";" << advLibrary[i].id << ";" << advLibrary[i].self << ";" << advLibrary[i].translation << ";" << advLibrary[i].note << ";";
			if (advLibrary[i].root == nullptr)
				cout << "0;";
			else
				cout << advLibrary[i].root->self << ";";
			cout << "#";
		}

		cout << endl << endl << "To quit, submit 'done' or 'd' " << endl;
		cin >> throwaway;
		if (throwaway == "done" || throwaway == "d")
			break;
		clearScreen();
	}

}

void parseDelim(string& text, list<Verb>& verbLibrary, list<Noun>& nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary)
{
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
			cout << temp_cat << endl;
			cout << i << " " << text[i + 1] << endl;
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
			list<int> roles = {};
			list<int> phrases = {};

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

			list<ThetaCell> thetaGrid = {};
			for (int p = 0; p < gridSize; p++)
			{
				thetaGrid.push_back(ThetaCell(roles[p], phrases[p]));
			}

			for (int h = 0; h < thetaGrid.size(); h++)
			{
				//cerr << "(" << thetaGrid[h].element << ", " << thetaGrid[h].type << ")" << endl;
			}

			verbLibrary.push_back(Verb(identity, name, meaning, thetaGrid));
		}

		if (cat == NOUN)
		{
			Verb* root = nullptr;
			string rootName = "";

			if (text[i] != '0')
			{
				cout << i << endl;
				while (text[i] != ';')
				{
					rootName += text[i];
					i++;
				}

                for (int k = 0; k < verbLibrary.size(); k++)
				{
					if (verbLibrary[k].self == rootName)
					{
						root = &verbLibrary[k];
					}
				}
				i--;
			}
			nounLibrary.push_back(Noun(identity, name, meaning, root, note));
			i += 3;
		}

		if (cat == ADJ)
		{
			Noun* root = nullptr;
			string rootName = "";

			if (text[i] != '0')
			{
				cout << i << endl;
				while (text[i] != ';')
				{
					rootName += text[i];
					i++;
				}

				for (int k = 0; k < nounLibrary.size(); k++)
				{
					if (nounLibrary[k].self == rootName)
					{
						root = &nounLibrary[k];
					}
				}
				i--;
			}
			adjLibrary.push_back(Adjective(identity, name, meaning, root, note));
			i += 3;
		}

		if (cat == ADV)
		{
			Adjective* root = nullptr;
			string rootName = "";

			if (text[i] != '0')
			{
				cout << i << endl;
				while (text[i] != ';')
				{
					rootName += text[i];
					i++;
				}

				for (int k = 0; k < adjLibrary.size(); k++)
				{
					if (adjLibrary[k].self == rootName)
					{
						root = &adjLibrary[k];
					}
				}
				i--;
			}
			advLibrary.push_back(Adverb(identity, name, meaning, root, note));
			i += 3;
		}
	}
}
*/
 
void uploadWords(list<Verb> &verbLibrary, list<Noun> &nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary)
{
	string throwaway;
	while (1)
	{
		cout << "paste here, or submit 'done' or 'd' to exit." << endl;

		string text;
		cin >> text;

		if (text == "done" || text == "d")
		{
			break;
		}
		
		parseDelim(text, verbLibrary, nounLibrary, adjLibrary, advLibrary);

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
	list<Verb> verbLibrary = { };
	list<Noun> nounLibrary = { };
	list<Adjective> adjLibrary = { };
	list<Adverb> advLibrary = { };
	list<Word> wordLibrary = { };
	list<string> corpus = { };

	cout << "Welcome to the Lexical Formatter, a tool that helps create and format all the words in your Conlang!" << endl;
	cout << "=========================" << endl;
	
	while (1)
	{
		cout << "You are now in the main menu, select an option to start: " << endl;
		cout << "(0) Set Seed  (1) Add Word  (2) Delete Word " << endl;
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
			cout << "Choose what to add:" << endl;
			cout << "(1) Verb  (2) Noun  (3) Adjective  (4) Adverb  " << endl;
			cin >> choice;

			clearScreen();
			switch (choice)
			{
			case 1:
				addVerbs(verbLibrary, corpus);
				break;
			case 2:
				addNouns(nounLibrary, verbLibrary, corpus);
				break;
			case 3:
				addAdjectives(adjLibrary, nounLibrary, corpus);
				break;
			case 4:
				addAdverbs(advLibrary, adjLibrary, corpus);
			}
			break;
		case 2:
			break;
		case 3:
			format(verbLibrary, nounLibrary, adjLibrary, advLibrary, corpus);
			break;
		case 4:
			generateDelim(verbLibrary, nounLibrary, adjLibrary, advLibrary);
			break;
		case 5:
			uploadWords(verbLibrary, nounLibrary, adjLibrary, advLibrary);
		}
		clearScreen();
	}

}

