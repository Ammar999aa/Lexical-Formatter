#ifndef IDH
#define IDH

#include <iostream>
#include <string>
#include <list>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <vector>

#include "global.h"


class Verb;

class ID
{
public:
    ID(int cat, int rootNumber, int derivationNumber);
    ID(int cat, int rootNumber, int derivationNumber, bool isDerived);
    int operator == (ID other);
    int operator != (ID other);
    
    int display() const;
    std::string displayAsString() const;
    int getCategory() const;
    bool getHasRoot() const;
    int getRoot() const;
    int getDerivation() const;
    
private:
    int category;
    bool hasRoot;
    int root;
    int derivation;
};

class ID_Manager
{
public:
    ID_Manager();
    ID generateID(int category, Verb* root, std::string derivedSelf);
    int derivationCount(ID id) const;
    
private:
    int rootTracker;
    std::vector<int> derivationTracker;
};

#endif
