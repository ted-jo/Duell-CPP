#pragma once
#include "stdafx.h"
#include "Die.h"

class Board
{
public:
	Board();
	~Board();
	void movePieceUp(int, int);
	void movePieceDown(int, int);
	void movePieceLeft(int, int);
	void movePieceRight(int, int);
	bool checkOccupiedSpace(int, int, string);
	//bool checkPath(int, int, int, int, int);
	bool checkNumSpaces(int, int, int, int);
	vector< vector<Die> > & GetBoard() { return gameboard; };
	void setBoard(vector<vector<Die>>);
	Die * dieSwitch(int, int, string);

private:
	vector< vector<Die> > gameboard;
};

