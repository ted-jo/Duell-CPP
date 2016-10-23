//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#pragma once
#include "stdafx.h"
#include "Die.h"

class Board
{
public:
	Board();
	~Board();

	// Accessor
	vector< vector<Die> > & GetBoard() { return gameboard; };
	// Mutator
	void setBoard(vector<vector<Die>>);

	void movePieceUp(int, int);
	void movePieceDown(int, int);
	void movePieceLeft(int, int);
	void movePieceRight(int, int);
	Die * dieSwitch(int, int, string);

private:
	vector< vector<Die> > gameboard;
};

