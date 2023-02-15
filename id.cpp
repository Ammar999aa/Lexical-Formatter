#include "id.h"
#include "Verb.h"

using namespace std;

ID::ID(int cat, int rootNumber, int derivationNumber)
    : category(cat), root(rootNumber), derivation(derivationNumber), hasRoot(1)
{
}

ID::ID(int cat, int rootNumber, int derivationNumber, bool isDerived)
    : category(cat), root(rootNumber), derivation(derivationNumber), hasRoot(isDerived)
{
}

int ID::operator == (ID other)
{
    if (root == other.root && derivation == other.derivation && category == other.category && hasRoot == other.hasRoot)
    {
        return 1;
    }
    return 0;
}

int ID::operator != (ID other)
{
    if (root != other.root || derivation != other.derivation || category != other.category || hasRoot != other.hasRoot)
    {
        return 1;
    }
    return 0;
}

int ID::display() const
{
    int magCat = category * 100000000;
    int magRoot = root * 10000;
    int magDerivation = derivation * 1;
    return (magCat + magRoot + magDerivation);
}

std::string ID::displayAsString() const
{
    return "";
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

ID ID_Manager::generateID(int category, Verb* root, string derivedSelf)
{
    int rootNumber = -1;
    int derivationNumber = -1;
    bool hasRoot = true;
    ID id = ID(rootNumber, derivationNumber, hasRoot);
    
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
        
        id = ID(category, rootNumber, derivationNumber, hasRoot);
        
        rootTracker++;
        derivationTracker.push_back(0);
    }
    else if (root == nullptr)
    {
        bool allFull = true;
        for (int i = 0; i < 5; i++)
        {
            if (derivationTracker[i] != 9999 && allFull == true)
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
        
        id = ID(category, rootNumber, derivationNumber, hasRoot);
        derivationTracker[rootNumber]++;
    }
    else
    {
        cout << root->getId().getRoot() << endl;
        rootNumber = root->getId().getRoot();
        derivationNumber = derivationTracker[rootNumber] + 1;
        derivationTracker[rootNumber]++;
        
        hasRoot = true;
        
        id = ID(category, rootNumber, derivationNumber, hasRoot);
        root->addDerived(id);
    }

    return id;
}

int ID_Manager::derivationCount(ID id) const
{
    int rootNumber = id.getRoot();
    return derivationTracker[rootNumber];
}
