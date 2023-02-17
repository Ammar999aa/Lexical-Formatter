#include <iostream>
#include <string>
#include <list>
#include <list>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "global.h"
#include "Word.h"
#include "Verb.h"
#include "Noun.h"
#include "Adjective.h"
#include "Adverb.h"
#include "id.h"
#include "format.h"

using namespace std;

void takeAPeak(list<string>& corpus)
{
    for (auto it = corpus.begin(); it != corpus.end(); it++)
    {
        cout << *it << endl;
    }
    
    string throwaway;
    cin >> throwaway;
}

void deleteWords(list<Verb>& verbLibrary, list<Noun>& nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary,  list<string>& corpus, ID_Manager& manager)
{
    cout << "you can now delete. Once finished, submit 'done' " << endl;
    
    while (1)
    {
        cout << "input the name of the adverb to delete. Once finished, submit 'done' " << endl;
        
        string name;
        cin >> name;
        
        if (name == "done" || name == "d")
        {
            clearScreen();
            break;
        }
        else
        {
            // find word in the libraries, aand print it.
            bool categoryFound = false;
            for (list<Verb>::iterator it = verbLibrary.begin(); it != verbLibrary.end(); it++)
            {
                if (it->getSelf() == name)
                {
                    categoryFound = true;
                    clearScreen();
                    cout << "word found and deleted: " << endl;
                    printVerb(verbLibrary, nounLibrary, adjLibrary, advLibrary, it);
                    deleteVerb(it, it->getSelf(), it->getDerivationID(), verbLibrary, nounLibrary, adjLibrary, advLibrary, corpus, manager);
                    break;
                }
            }
            if (!categoryFound)
            {
                for (list<Noun>::iterator it = nounLibrary.begin(); it != nounLibrary.end(); it++)
                {
                    if (it->getSelf() == name)
                    {
                        categoryFound = true;
                        clearScreen();
                        cout << "word found and deleted: " << endl;
                        printNoun(it);
                        deleteNoun(it, it->getSelf(), nounLibrary, verbLibrary, corpus, manager);
                        break;
                    }
                }
            }
            if (!categoryFound)
            {
                for (list<Adjective>::iterator it = adjLibrary.begin(); it != adjLibrary.end(); it++)
                {
                    if (it->getSelf() == name)
                    {
                        categoryFound = true;
                        clearScreen();
                        cout << "word found and deleted: " << endl;
                        printAdj(it);
                        deleteAdjective(it, it->getSelf(), adjLibrary, verbLibrary, corpus, manager);
                        break;
                    }
                }
            }
            if (!categoryFound)
            {
                for (list<Adverb>::iterator it = advLibrary.begin(); it != advLibrary.end(); it++)
                {
                    if (it->getSelf() == name)
                    {
                        categoryFound = true;
                        clearScreen();
                        cout << "word found and deleted: " << endl;
                        printAdv(it);
                        deleteAdverb(it, it->getSelf(), advLibrary, verbLibrary, corpus, manager);
                        break;
                    }
                }
            }
            if (!categoryFound)
            {
                cout << name << " " << "info not found" << endl;
            }
        }
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
            cout << setw(10) << setfill('0') << verbIt->getId().display();
            
            cout << ";" << verbIt->getSelf() << ";" << verbIt->getTranslation() << ";" << verbIt->getNote() << ";";
			cout << verbIt->getGrid().size() << ";";
            
            list<ThetaCell> tempGrid = verbIt->getGrid();
            list<ThetaCell>::iterator thetaIt;
			for (thetaIt = tempGrid.begin(); thetaIt != tempGrid.end(); thetaIt++)
			{
				cout << thetaIt->element << ";" << thetaIt->type << ";";
			}
			cout << "#";
		}
        
        list<Noun>::iterator nounIt;
		for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
		{
            cout << nounIt->getCategory() << ";" << setw(10) << setfill('0') << nounIt->getId().display();
            cout << ";" << nounIt->getSelf() << ";" << nounIt->getTranslation() << ";" << nounIt->getNote() << ";";
			if (nounIt->getRoot() == nullptr)
				cout << "0;";
			else
				cout << nounIt->getRoot()->getSelf() << ";";
			cout << "#";
		}
        
        list<Adjective>::iterator adjIt;
		for (adjIt = adjLibrary.begin() ; adjIt != adjLibrary.end(); adjIt++)
		{
            cout << adjIt->getCategory() << ";" << setw(10) << setfill('0') << adjIt->getId().display();
            cout << ";" << adjIt->getSelf() << ";" << adjIt->getTranslation() << ";" << adjIt->getNote() << ";";
			if (adjIt->getRoot() == nullptr)
				cout << "0;";
			else
				cout << adjIt->getRoot()->getSelf() << ";";
			cout << "#";
		}

        list<Adverb>::iterator advIt;
		for (advIt = advLibrary.begin() ; advIt != advLibrary.end(); advIt++)
		{
            cout << advIt->getCategory() << ";" << setw(10) << setfill('0') << advIt->getId().display();
            cout << ";" << advIt->getSelf() << ";" << advIt->getTranslation() << ";" << advIt->getNote() << ";";
			if (advIt->getRoot() == nullptr)
				cout << "0;";
			else
				cout << advIt->getRoot()->getSelf() << ";";
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
		ID identity = ID(-1, -1, -1);
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

        /*
		for (int k = temp_id.size() - 1; k > -1; k--)
		{
			identity += temp_id[k] * pow(10, (temp_id.size() - k - 1)) - 48;
		}
        */

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
					if (verbIt->getSelf() == rootName)
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
					if (nounIt->getSelf() == rootName)
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
					if (adjIt->getSelf() == rootName)
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
	list<Verb> verbLibrary = { };
	list<Noun> nounLibrary = { };
	list<Adjective> adjLibrary = { };
	list<Adverb> advLibrary = { };
	list<Word> wordLibrary = { };
	list<string> corpus = { };
    
    ID_Manager manager = ID_Manager();

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
				addVerbs(verbLibrary, corpus, manager);
				break;
			case 2:
				addNouns(nounLibrary, verbLibrary, corpus, manager);
				break;
			case 3:
				addAdjectives(adjLibrary, nounLibrary, corpus, manager);
				break;
			case 4:
				addAdverbs(advLibrary, adjLibrary, corpus, manager);
                break;
            }
			break;
		case 2:
            deleteWords(verbLibrary, nounLibrary, adjLibrary, advLibrary, corpus, manager);
			break;
		case 3:
            cout << "Choose sorting:" << endl;
            cout << "(1) Type  (2) Alpha  " << endl;
            cin >> choice;
                
            clearScreen();
            switch (choice)
            {
                case 1:
                    format(verbLibrary, nounLibrary, adjLibrary, advLibrary, corpus, manager);
                    break;
                case 2:
                    formatAlphabetically(verbLibrary, nounLibrary, adjLibrary, advLibrary, corpus, manager);
                    break;
                case 3:
                    takeAPeak(corpus);
                    break;
            }
            break;
		case 4:
			generateDelim(verbLibrary, nounLibrary, adjLibrary, advLibrary);
			break;
		case 5:
			uploadWords(verbLibrary, nounLibrary, adjLibrary, advLibrary);
            break;
		}
		clearScreen();
	}

}

