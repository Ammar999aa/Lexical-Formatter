#ifndef VERBH
#define VERBH

#include "Word.h"
#include <vector>

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
	Verb(int identity, std::string name, std::string meaning, std::vector<ThetaCell> thetaGrid, std::string note);
	Verb(int identity, std::string name, std::string meaning, std::vector<ThetaCell> thetaGrid);

	std::vector<ThetaCell> grid;
	//for now
	std::string childNoun;
	std::string childAdj;
	std::string childAdv;
};

std::string getRandomRoot(std::vector<std::string>& corpus);

void addVerbs(std::vector<Verb>& library, std::vector<std::string>& corpus);

const std::vector<ThetaCell> gridEat = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP) };
const std::vector<ThetaCell> gridWant = { ThetaCell(EXPERIENCER, DP), ThetaCell(THEME, CP) };
const std::vector<ThetaCell> gridGo = { ThetaCell(EXPERIENCER, DP), ThetaCell(GOAL, PP) };
const std::vector<ThetaCell> gridSleep = { ThetaCell(EXPERIENCER, DP) };
const std::vector<ThetaCell> gridPut = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP), ThetaCell(GOAL, PP) };

#endif