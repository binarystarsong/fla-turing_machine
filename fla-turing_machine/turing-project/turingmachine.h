#ifndef __TURINGMACHINE_H__
#define __TURINGMACHINE_H__
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>
using namespace std;
struct TransitionFunction{
    string curState;
    vector<char> oldSymbol;
    vector<char> newSymbol;
    vector<int> direction;
    string newState;
};
struct TuringMachine{
    vector<string> state;
    vector<char> input;
    vector<char> tapestate;
    string start;
    string blank;
    vector<string> finalstate;
    int tapenum;
    vector<TransitionFunction> delta;
};
TuringMachine readtxt(string filename);
#endif
