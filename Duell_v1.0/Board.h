#pragma once
#include "stdafx.h"
#include "Die.h"

class Board
{
public:
	Board();
	~Board();
	void movePieceDown(int, int, vector<vector<Die>> &);
	bool legalMove(int, int);
	vector< vector<Die> > & GetBoard() { return gameboard; };
	void setBoard(vector<vector<Die>>);
private:
	vector< vector<Die> > gameboard;
};

