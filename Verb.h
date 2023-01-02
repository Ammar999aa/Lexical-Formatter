#ifndef VERB
#define VERB

#include <iostream>
#include <string>
#include <cstdlib>
#include "global.h"
#include <vector>
#include "Word.h"

using namespace std;

struct ThetaCell
{
	ThetaCell(int role, int phrase)
		: element(role), type(phrase) {}

	int element; // example: Agent, Theme...
	int type; // example: DP, PP...
};


class Verb : public Word
{
public:
	Verb(int identity, string name, string meaning, vector<ThetaCell> thetaGrid, string note)
		: Word(identity, name, meaning, note), grid(thetaGrid) {}
	Verb(int identity, string name, string meaning, vector<ThetaCell> thetaGrid)
		: Word(identity, name, meaning), grid(thetaGrid) {}

	vector<ThetaCell> grid;
};


const vector<ThetaCell> gridEat = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP) };
const vector<ThetaCell> gridWant = { ThetaCell(EXPERIENCER, DP), ThetaCell(THEME, CP) };
const vector<ThetaCell> gridGo = { ThetaCell(EXPERIENCER, DP), ThetaCell(GOAL, PP) };
const vector<ThetaCell> gridSleep = { ThetaCell(EXPERIENCER, DP) };
const vector<ThetaCell> gridPut = { ThetaCell(AGENT, DP), ThetaCell(THEME, DP), ThetaCell(GOAL, PP) };

#endif