#pragma once
#include "stdafx.h"
#include "Die.h"

class Board
{
public:
	Board();
	~Board();
	vector<vector<Die>> movePiece(int, int, vector<vector<Die>> &);
	vector< vector<Die> > & GetBoard() { return gameboard; };
private:
	vector< vector<Die> > gameboard;
};

