#include "stdafx.h"
#include "Board.h"
#include "boardView.h"

#pragma once
class Player
{
public:
	Player();
	~Player();
	// Play is virtual so its overwritten in Human and Player. It will control a single turn of play
	virtual Board * play() = 0;
	Board getBoard() { return * boardObj; }
	void setBoard(Board *);
	bool checkOOB(int, int);
	bool validateMove(int, int, int, int, int, string);
	vector<int> getKeypieceLoc(string);
	void setWin(string);
	bool checkHumanWin();

	int getDirection(int, int, int, int);
	bool getPath(int, int, int, int, int, bool);
	bool checkVerticalPath(int, int, int, int, bool);
	bool checkHorizontalPath(int, int, int, int, bool);

	// TODO: Finish fixing AI Passes

	// Computer AI Functions
	// First Pass
	bool keyPieceAttack(string);
	// Second Pass
	bool protectKeyPiece();
	bool executeBlock(int, int);
	// Third Pass
	// Check for move that will overtake an opponent's piece
	bool checkOvertake(int, int, int, int);
	// Fourth Pass Move piece that can get closest
	// to opponent keypiece/space
	void findBestMove();
	vector<int> checkBestMove(int, int);
	int executeClosestMove(int, int, int, int);
protected:
	Board * boardObj;
private:
	int humanWin;
	int computerWin;
};

