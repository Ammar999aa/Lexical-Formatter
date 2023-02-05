#ifndef VERBH
#define VERBH

#include "Word.h"
#include <list>

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
	Verb(int identity, std::string name, std::string meaning, std::list<ThetaCell> thetaGrid, std::string note);
	Verb(int identity, std::string name, std::string meaning, std::list<ThetaCell> thetaGrid);

	std::list<ThetaCell> grid;
	//for now
	std::list<Noun*> childNoun;
	std::list<Adjective*> childAdj;
	std::list<Adverb*> childAdv;
};

std::string getRandomRoot(std::list<std::string>& corpus);

void addVerbs(std::list<Verb>& library, std::list<std::string>& corpus);

const std::list<ThetaCell> gridEat = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP) };
const std::list<ThetaCell> gridWant = { ThetaCell(EXPERIENCER, DP), ThetaCell(THEME, CP) };
const std::list<ThetaCell> gridGo = { ThetaCell(EXPERIENCER, DP), ThetaCell(GOAL, PP) };
const std::list<ThetaCell> gridSleep = { ThetaCell(EXPERIENCER, DP) };
const std::list<ThetaCell> gridPut = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP), ThetaCell(GOAL, PP) };

#endif
