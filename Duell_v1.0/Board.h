#pragma once
#include "stdafx.h"
#include "Die.h"

class Board
{
public:
	Board();
	~Board();
	void MovePiece();
	vector< vector<Die> > & GetBoard() { return gameboard; };
private:
	vector< vector<Die> > gameboard;
};

