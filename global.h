#ifndef GLOBALH
#define GLOBALH

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

const int CLUSTER_CHANCE = 5;
const string ONSET_NO_CLUSTER[15] = { "t", "p", "r", "n", "d", "m", "s", "k", "b", "f", "g", "l", "v", "j", "x" };
const string CODA[16] = { "n", "r", "m", "l", "p", "t", "d", "ng", "s", "v", "j", "k", "x", "b", "f", "g" };
const string ONSET_CLUSTER[13] = { "t", "p", "d", "s", "k", "b", "f", "g", "v", "s", "j", "x", "j" };
const string NUCLEUS[7] = { "e", "u", "a", "ee", "oo", "i", "o" };

const string PLOSIVE_V_CLUSTER[2] = { "r", "l" };
const string F_CLUSTER[3] = { "r", "l", "x" };
const string S_CLUSTER[8] = { "p", "t", "k", "r", "l", "n", "m", "x" };
const string J_CLUSTER[7] = { "r", "l", "n", "m", "b", "d", "g" };
const string X_CLUSTER[4] = { "n", "m", "r", "l" };

// const int VERB = 0;
const int AGENT = 1;
const int EXPERIENCER = 2;
const int THEME = 3;
const int GOAL = 4;
const int LOCATION = 5;
const int BENEFICIARY = 6;
const int RECEPIENT = 7;

const int DP = 0;
const int PP = 1;
const int CP = 2;
const int AdjP = 3;
const int AdvP = 4;
const int VP = 5;

const int VERB = 0;
const int NOUN = 1;
const int ADJ = 2;
const int ADV = 3;
const int DET = 4;
const int CONJ = 6;
const int COMP = 7;
const int NEG = 8;
const int TENS = 9;

#endif // !GLOBAL