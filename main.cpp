#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <list>
#include <list>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>
#include <iomanip>

#include "global.h"
#include "Word.h"
#include "Verb.h"
#include "Noun.h"
#include "Adjective.h"
#include "Adverb.h"
#include "id.h"

using namespace std;

void format(list<Verb> & verbLibrary, list<Noun> & nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary, list<string> & corpus, ID_Manager& manager)
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
            cout << verbIt->getSelf() << " - " << verbIt->getTranslation() << " (" << categories[verbIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << verbIt->getId().display() << endl;
			// traverse through the grid of the verb and print each emelent along with its type
			cout << "	| ";
            
            list<ThetaCell> tempGrid = verbIt->getGrid();
            list<ThetaCell>::iterator thetaIt;
			for (thetaIt = tempGrid.begin(); thetaIt != tempGrid.end(); thetaIt++)
			{
                cout << elements[thetaIt->element] << " (" << types[thetaIt->type] << ") | ";
			}
			
			cout << endl << "	derived:" << endl;
			
            for (int i = 0; i < verbIt->getDerivationID().size(); i++)
            {
                int derivedCategory = verbIt->getDerivationID()[i].getCategory();
                
                switch (derivedCategory)
                {
                    case NOUN:
                        for (list<Noun>::iterator nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
                        {
                            if (nounIt->getId() == verbIt->getDerivationID()[i])
                            {
                                cout << "       " << nounIt->getSelf() << " (" << categories[NOUN] << ")" << endl;
                                break;
                            }
                        }
                        break;
                    case ADJ:
                        for (list<Adjective>::iterator adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
                        {
                            if (adjIt->getId() == verbIt->getDerivationID()[i])
                            {
                                cout << adjIt->getSelf() << " (" << categories[ADJ] << ")" << endl;
                                break;
                            }
                        }
                        break;
                    case ADV:
                        for (list<Adverb>::iterator advIt = advLibrary.begin(); advIt != advLibrary.end(); advIt++)
                        {
                            if (advIt->getId() == verbIt->getDerivationID()[i])
                            {
                                cout << advIt->getSelf() << " (" << categories[ADV] << ")" << endl;
                                break;
                            }
                        }
                        break;
                }
            }

			cout << endl;
		}
        
        list<Noun>::iterator nounIt;
		for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
		{
			cout << nounIt->getSelf() << " - " << nounIt->getTranslation() << " (" << categories[nounIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << nounIt->getId().display() << endl;
			
			if (nounIt->getRoot() != nullptr)
				cout << "	from: " << nounIt->getRoot()->getSelf() << endl;

			cout << endl;
		}
        
        list<Adjective>::iterator adjIt;
		for (adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
		{
			cout << adjIt->getSelf() << " - " << adjIt->getTranslation() << " (" << categories[adjIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << adjIt->getId().display() << endl;

			if (adjIt->getRoot() != nullptr)
				cout << "	from: " << adjIt->getRoot()->getSelf() << endl;

			cout << endl;
		}
        
        list<Adverb>::iterator advIt;
        for (advIt = advLibrary.begin(); advIt != advLibrary.end(); advIt++)
        {
            cout << advIt->getSelf() << " - " << advIt->getTranslation() << " (" << categories[advIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << advIt->getId().display() << endl;

            if (advIt->getRoot() != nullptr)
                cout << "    from: " << advIt->getRoot()->getSelf() << endl;

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

    string outfile_path = "/Users/abdulaziz/Cloud/Software Dev/Lexical-Formatter/data.csv";
    ofstream outFile;
    outFile.open(outfile_path);
    if (outFile.is_open()) {
        while (true)
        {
            list<Verb>::iterator verbIt;
            for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
            {
                outFile << verbIt->getId().display() << ",";
                outFile << verbIt->getSelf() << "," << verbIt->getTranslation() << "," << verbIt->getNote() << ",";
                outFile << verbIt->getGrid().size() << ",";
                list<ThetaCell> tempGrid = verbIt->getGrid();
                list<ThetaCell>::iterator thetaIt;
                for (thetaIt = tempGrid.begin(); thetaIt != tempGrid.end(); thetaIt++)
                {
                    outFile << thetaIt->element << "," << thetaIt->type << ",";
                }
                outFile << "\n";
            }
            
            list<Noun>::iterator nounIt;
            for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
            {
                outFile << nounIt->getCategory() << "," << nounIt->getId().display() << ",";
                outFile << nounIt->getSelf() << "," << nounIt->getTranslation() << "," << nounIt->getNote() << ",";
                if (nounIt->getRoot() == nullptr)
                    outFile << "0,";
                else
                    outFile << nounIt->getRoot()->getSelf() << ",";
                outFile << "\n";
            }
            
            list<Adjective>::iterator adjIt;
            for (adjIt = adjLibrary.begin() ; adjIt != adjLibrary.end(); adjIt++)
            {
                outFile << adjIt->getCategory() << "," << adjIt->getId().display() << ",";
                outFile << adjIt->getSelf() << "," << adjIt->getTranslation() << "," << adjIt->getNote() << ",";
                if (adjIt->getRoot() == nullptr)
                    outFile << "0,";
                else
                    outFile << adjIt->getRoot()->getSelf() << ",";
                outFile << "\n";
            }

            list<Adverb>::iterator advIt;
            for (advIt = advLibrary.begin() ; advIt != advLibrary.end(); advIt++)
            {
                outFile << advIt->getCategory() << "," << advIt->getId().display() << ",";
                outFile << advIt->getSelf() << "," << advIt->getTranslation() << "," << advIt->getNote() << ",";
                if (advIt->getRoot() == nullptr)
                    outFile << "0,";
                else
                    outFile << advIt->getRoot()->getSelf() << ",";
                outFile << "\n";
            }

            outFile << "\nTo quit, submit 'done' or 'd' \n";
           string input;
           getline(cin, input);
           if (input.empty() || input[0] == 'd') {
               break;
           }
           clearScreen();
        }
        outFile.close();
        cout << "Data saved to " << "data.csv" << " successfully." << endl;
    }
    else {
        cout << "Error opening " << "data.csv" << " for writing." << endl;
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
			}
			break;
		case 2:
			break;
		case 3:
			format(verbLibrary, nounLibrary, adjLibrary, advLibrary, corpus, manager);
			break;
		case 4:
            {
            generateDelim(verbLibrary, nounLibrary, adjLibrary, advLibrary);
            }
            break;
		case 5:
//			readDelim(verbLibrary, nounLibrary, adjLibrary, advLibrary);
            break;

        case 6:
            return 0;
            break;
            
		}
        
		clearScreen();
	}

}

