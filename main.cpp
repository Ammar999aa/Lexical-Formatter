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
			
            list<Noun*>::iterator nounIt;
            for (nounIt = verbIt->childNoun.begin(); nounIt != verbIt->childNoun.end(); nounIt++)
            {
                cout << "    " << (*nounIt)->self << " (n)" << endl; //what in the ??
            }
            list<Adjective*>::iterator adjIt;
            for (adjIt = verbIt->childAdj.begin(); adjIt != verbIt->childAdj.end(); adjIt++)
			{
				cout << "	" << (*adjIt)->self << " (Adj)" << endl;
			}
            list<Adverb*>::iterator advIt;
            for (advIt = verbIt->childAdv.begin(); advIt != verbIt->childAdv.end(); advIt++)
			{
				cout << "	" << (*advIt)->self << " (Adv)" << endl;
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
	
	string throwaway;
	while (1)
	{
        list<Verb>::iterator verbIt;
		for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
		{
			cout << verbIt->category << ";" << verbIt->id << ";" << verbIt->self << ";" << verbIt->translation << ";" << verbIt->note << ";";
			cout << verbIt->grid.size() << ";";
            
            list<ThetaCell>::iterator thetaIt;
			for (thetaIt = verbIt->grid.begin(); thetaIt != verbIt->grid.end(); thetaIt++)
			{
				cout << thetaIt->element << ";" << thetaIt->type << ";";
			}
			cout << "#";
		}
        
        list<Noun>::iterator nounIt;
		for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
		{
			cout << nounIt->category << ";" << nounIt->id << ";" << nounIt->self << ";" << nounIt->translation << ";" << nounIt->note << ";";
			if (nounIt->root == nullptr)
				cout << "0;";
			else
				cout << nounIt->root->self << ";";
			cout << "#";
		}
        
        list<Adjective>::iterator adjIt;
		for (adjIt = adjLibrary.begin() ; adjIt != adjLibrary.end(); adjIt++)
		{
			cout << adjIt->category << ";" << adjIt->id << ";" << adjIt->self << ";" << adjIt->translation << ";" << adjIt->note << ";";
			if (adjIt->root == nullptr)
				cout << "0;";
			else
				cout << adjIt->root->self << ";";
			cout << "#";
		}

        list<Adverb>::iterator advIt;
		for (advIt = advLibrary.begin() ; advIt != advLibrary.end(); advIt++)
		{
			cout << advIt->category << ";" << advIt->id << ";" << advIt->self << ";" << advIt->translation << ";" << advIt->note << ";";
			if (advIt->root == nullptr)
				cout << "0;";
			else
				cout << advIt->root->self << ";";
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
                
                list<Verb>::iterator verbIt;
                for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
				{
					if (verbIt->self == rootName)
					{
						root = &*verbIt;
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
                
                list<Noun>::iterator nounIt;
                for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
				{
					if (nounIt->self == rootName)
					{
						root = &*nounIt;
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
                
                list<Adjective>::iterator adjIt;
				for (adjIt = adjLibrary.begin();  adjIt != adjLibrary.end(); adjIt++)
				{
					if (adjIt->self == rootName)
					{
						root = &*adjIt;
					}
				}
				i--;
			}
			advLibrary.push_back(Adverb(identity, name, meaning, root, note));
			i += 3;
		}
	}
}

 
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

