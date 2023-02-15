#ifndef VERBH
#define VERBH

#include "Word.h"
#include <list>
#include "id.h"

class Noun;
class Adjective;
class Adverb;

struct ThetaCell
{
	ThetaCell(int role, int phrase);

	int element; // example: Agent, Theme...
	int type; // example: DP, PP...
};

class Verb : public Word
{
public:
	Verb(ID identity, std::string name, std::string meaning, std::list<ThetaCell> thetaGrid, std::string note);
	Verb(ID identity, std::string name, std::string meaning, std::list<ThetaCell> thetaGrid);
    //acessors
    std::list<ThetaCell> getGrid() const;
    std::list<Noun*> getChildNoun() const;
    std::list<Adjective*> getChildAdj() const;
    std::list<Adverb*> getChildAdv() const;
    std::vector<ID> getDerivationID() const;
    
    //mutators
    void addDerived(ID id);
    
private:
	std::list<ThetaCell> grid;
    std::vector<ID> derivedId;
    
	std::list<Noun*> childNoun;
	std::list<Adjective*> childAdj;
	std::list<Adverb*> childAdv;
};

std::string getRandomRoot(std::list<std::string>& corpus);

void addVerbs(std::list<Verb>& library, std::list<std::string>& corpus, ID_Manager& manager);

const std::list<ThetaCell> gridEat = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP) };
const std::list<ThetaCell> gridWant = { ThetaCell(EXPERIENCER, DP), ThetaCell(THEME, CP) };
const std::list<ThetaCell> gridGo = { ThetaCell(EXPERIENCER, DP), ThetaCell(GOAL, PP) };
const std::list<ThetaCell> gridSleep = { ThetaCell(EXPERIENCER, DP) };
const std::list<ThetaCell> gridPut = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP), ThetaCell(GOAL, PP) };

#endif
