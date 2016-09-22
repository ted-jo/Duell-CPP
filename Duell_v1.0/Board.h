#pragma once
#include "stdafx.h"
#include "Die.h"

class Board
{
public:
	Board();
	~Board();
	void movePieceDown(int, int);
	bool checkOOB(int, int);
	bool occupiedSpace(int, int);
	vector< vector<Die> > & GetBoard() { return gameboard; };
	void setBoard(vector<vector<Die>>);
private:
	vector< vector<Die> > gameboard;
};

