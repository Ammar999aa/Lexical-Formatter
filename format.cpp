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

void printVerb(list<Verb>& verbLibrary, list<Noun>& nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary, list<Verb>::iterator verbIt)
{
    vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
    vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
    vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };
    
        cout << verbIt->getSelf() << " - " << verbIt->getTranslation() << " (" << categories[verbIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << verbIt->getId().display() << endl;
        // traverse through the grid of the verb and print each emelent along with its type
        cout << "    | ";
        
        list<ThetaCell> tempGrid = verbIt->getGrid();
        list<ThetaCell>::iterator thetaIt;
        for (thetaIt = tempGrid.begin(); thetaIt != tempGrid.end(); thetaIt++)
        {
            cout << elements[thetaIt->element] << " (" << types[thetaIt->type] << ") | ";
        }
        
        cout << endl << "    derived:" << endl;
        
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
                            cout << "       " << adjIt->getSelf() << " (" << categories[ADJ] << ")" << endl;
                            break;
                        }
                    }
                    break;
                case ADV:
                    for (list<Adverb>::iterator advIt = advLibrary.begin(); advIt != advLibrary.end(); advIt++)
                    {
                        if (advIt->getId() == verbIt->getDerivationID()[i])
                        {
                            cout << "       " << advIt->getSelf() << " (" << categories[ADV] << ")" << endl;
                            break;
                        }
                    }
                    break;
            }
        }
        cout << endl;
}

void printNoun(list<Noun>::iterator nounIt)
{
    vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
    vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
    vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };
    
    cout << nounIt->getSelf() << " - " << nounIt->getTranslation() << " (" << categories[nounIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << nounIt->getId().display() << endl;
    
    if (nounIt->getRoot() != nullptr)
        cout << "    from: " << nounIt->getRoot()->getSelf() << endl;

    cout << endl;
}

void printAdj(list<Adjective>::iterator adjIt)
{
    vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
    vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
    vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };
    
    cout << adjIt->getSelf() << " - " << adjIt->getTranslation() << " (" << categories[adjIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << adjIt->getId().display() << endl;

    if (adjIt->getRoot() != nullptr)
        cout << "    from: " << adjIt->getRoot()->getSelf() << endl;

    cout << endl;
}

void printAdv(list<Adverb>::iterator advIt)
{
    vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
    vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
    vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };
    
    cout << advIt->getSelf() << " - " << advIt->getTranslation() << " (" << categories[advIt->getCategory()] << ")" << " ID: " << setw(10) << setfill('0') << advIt->getId().display() << endl;

    if (advIt->getRoot() != nullptr)
        cout << "    from: " << advIt->getRoot()->getSelf() << endl;

    cout << endl;
}

void formatAlphabetically(list<Verb> & verbLibrary, list<Noun> & nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary, list<string> corpus, ID_Manager& manager) // corpus is copied
{
    vector<string> elements = { "Verb", "Agent", "Experiencer", "Theme", "Goal", "Location", "Beneficiary", "Recipient" };
    vector<string> types = { "DP", "PP" , "CP", "AdjP", "AdvP", "VP" };
    vector<string> categories = { "v", "n", "Adj", "Adv", "Det" };
    
    string throwaway;
    while (1)
    {
        vector<string> sortedCorpus = {};
        for (list<string>::iterator corpusIt = corpus.begin(); corpusIt != corpus.end(); corpusIt++)
        {
            sortedCorpus.push_back(*corpusIt);
        }
        
        sort(sortedCorpus.begin(), sortedCorpus.end());
        
        for (int i = 0; i < sortedCorpus.size(); i += 2) // for some reason i has to increment by 2 otherwise it will print doubles.
        {
            bool wordFound = false;
            
            for (list<Verb>::iterator it = verbLibrary.begin(); it != verbLibrary.end(); it++)
            {
                if (it->getSelf() == sortedCorpus[i])
                {
                    wordFound = true;
                    printVerb(verbLibrary, nounLibrary, adjLibrary, advLibrary, it);
                    break;
                }
            }
            if (wordFound)
            {
                continue;
            }
            for (list<Noun>::iterator it = nounLibrary.begin(); it != nounLibrary.end(); it++)
            {
                if (it->getSelf() == sortedCorpus[i])
                {
                    wordFound = true;
                    printNoun(it);
                    break;
                }
            }
            if (wordFound)
            {
                continue;
            }
            for (list<Adjective>::iterator it = adjLibrary.begin(); it != adjLibrary.end(); it++)
            {
                if (it->getSelf() == sortedCorpus[i])
                {
                    wordFound = true;
                    printAdj(it);
                    break;
                }
            }
            if (wordFound)
            {
                continue;
            }
            for (list<Adverb>::iterator it = advLibrary.begin(); it != advLibrary.end(); it++)
            {
                if (it->getSelf() == sortedCorpus[i])
                {
                    wordFound = true;
                    printAdv(it);
                    break;
                }
            }
            if (!wordFound)
            {
                cout << sortedCorpus[i] << " " << "info not found" << endl;
            }
        }
        
        cout << "To quit, submit 'done' or 'd' " << endl;
        cin >> throwaway;
        if (throwaway == "done" || throwaway == "d")
            break;
        clearScreen();
        
    }
}

void format(list<Verb> & verbLibrary, list<Noun> & nounLibrary, list<Adjective>& adjLibrary, list<Adverb>& advLibrary, list<string> & corpus, ID_Manager& manager)
{
    string throwaway;
    while (1)
    {
        list<Verb>::iterator verbIt;
        for (verbIt = verbLibrary.begin(); verbIt != verbLibrary.end(); verbIt++)
        {
            printVerb(verbLibrary, nounLibrary, adjLibrary, advLibrary, verbIt);
        }
        
        list<Noun>::iterator nounIt;
        for (nounIt = nounLibrary.begin(); nounIt != nounLibrary.end(); nounIt++)
        {
            printNoun(nounIt);
        }
        
        list<Adjective>::iterator adjIt;
        for (adjIt = adjLibrary.begin(); adjIt != adjLibrary.end(); adjIt++)
        {
            printAdj(adjIt);
        }
        
        list<Adverb>::iterator advIt;
        for (advIt = advLibrary.begin(); advIt != advLibrary.end(); advIt++)
        {
            printAdv(advIt);
        }

        cout << "To quit, submit 'done' or 'd' " << endl;
        cin >> throwaway;
        if (throwaway == "done" || throwaway == "d")
            break;
        clearScreen();
    }
}
