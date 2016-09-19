#pragma once
#include "stdafx.h"

class Board
{
public:
	Board() : gameboard(8, vector <string>(9)) {}
	~Board();
	void MovePiece();
	void ResetBoard(vector< vector<string> > & gameboard);
	vector< vector<string> > & GetBoard() { return gameboard; };
private:
	vector< vector<string> > gameboard;
};

