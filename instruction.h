#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_
#include <cstring>
#include <vector>
#include "point.h"
using namespace std;

class instruction{
public:
	instruction( int lineNum, string opCode, string op1, string op2 = "0", string op3 = "0");
	int getLength();
	void convertNum(vector<point> points, int address);
	string writeWord(int &address);
	//~instruction();
private:
	char Op;
	string A;
	string B;
	string Data;
	bool isData;
	int Len;
	int sourceLine;
	string RegisterNibble(string reg);
	string toBinary(vector<point> points, string input);
	void error(int errorNum);
};

#endif
