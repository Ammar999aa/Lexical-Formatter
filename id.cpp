#include "id.h"

using namespace std;

ID::ID(int cat, int rootNumber, int derivationNumber)
    : category(cat), root(rootNumber), derivation(derivationNumber), hasRoot(1)
{
}

ID::ID(int cat, int rootNumber, int derivationNumber, bool isDerived)
    : category(cat), root(rootNumber), derivation(derivationNumber), hasRoot(isDerived)
{
}

int ID::display() const
{
    return -1;
}

int ID::getCategory() const
{
    return category;
}

bool ID::getHasRoot() const
{
    return hasRoot;
}

int ID::getRoot() const
{
    return root;
}

int ID::getDerivation() const
{
    return derivation;
}

ID_Manager::ID_Manager()
    : rootTracker(4)
{
    derivationTracker = { 0, 0, 0, 0, 0 };
}

ID ID_Manager::generateID(int category, Verb* root)
{
    int rootNumber;
    int derivationNumber;
    bool hasRoot;
    
    if (category == VERB)
    {
        if (rootTracker == 9999)
        {
            cout << "error: root limit reached" << endl;
            return ID(-1, -1, -1);
        }
        
        rootNumber = rootTracker + 1;
        derivationNumber = 0;
        hasRoot = false;
        
        ID id = ID(category, rootNumber, derivationNumber, hasRoot);
        
        rootTracker++;
        derivationTracker.push_back(0);
    }
    else if (root == nullptr)
    {
        bool allFull = true;
        for (int i = 0; i < 5; i++)
        {
            if (derivationTracker[i] != 9999)
            {
                allFull = false;
                rootNumber = i;
                derivationNumber = derivationTracker[i] + 1;
            }
        }
        
        if (allFull == true)
        {
            cout << "error: rootless word limit reached" << endl;
            return ID(-1, -1, -1);
        }
        
        hasRoot = false;
        
        ID id = ID(category, rootNumber, derivationNumber, hasRoot);
        derivationTracker[rootNumber]++;
    }
    else
    {
        return ID(-1, -1, -1);
        
        
        
    }

    return ID(-1, -1, -1);
}
