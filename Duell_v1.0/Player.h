//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "stdafx.h"
#include "Board.h"
#include "boardView.h"

#pragma once
class Player
{
public:
	Player();
	~Player() { delete boardObj; }
	// Play is virtual so its overwritten in Human and Player. It will control a single turn of play
	virtual Board * play() = 0;
	// Accessor function
	Board getBoard() const { return * boardObj; }
	// Mutator function
	void setBoard(Board *);

	// Logic Functions
	bool checkOOB(int, int);
	bool validateMove(int, int, int, int, int, string);
	vector<int> getKeypieceLoc(string);
	bool checkHumanWin();
	bool checkComputerWin();
	int getDirection(int, int, int, int);
	bool getPath(int, int, int, int, int, bool);
	bool checkVerticalPath(int, int, int, int, bool);
	bool checkHorizontalPath(int, int, int, int, bool);
	void displayMove(int, int, int, int, int, int);
	void help();
	void displayHelp(int, int, int, int, int, string);
	bool checkNumSpaces(int, int, int, int);
	bool checkOccupiedSpace(int, int, string);


	// ***** AI Functions *****
	// Check if Piece can attack the key piece or key space
	bool keyPieceAttack(string, bool);
	// Second Pass
	bool protectKeyPiece(string, bool);
	bool executeBlock(int, int, bool);
	// Third Pass
	// Check for move that will overtake an opponent's piece
	bool checkOvertake(string);
	// Fourth Pass Move piece that can get closest
	// to opponent keypiece/space
	bool executeBestMove();
protected:
	Board * boardObj;
};

