#include "stdafx.h"
#include "Board.h"
#include "boardView.h"

#pragma once
class Player
{
public:
	//TODO: Change constructor since its creating 2 new objects
	Player();
	~Player();
	// Play is virtual so its overwritten in Human and Player. It will control a single turn of play
	virtual Board * play() = 0;
	Board getBoard() { return * boardObj; }
	void setBoard(Board *);
	bool checkOOB(int, int);
	bool validateMove(int, int, int, int, int, string);
	void executeMove(int, int, int, int, int, string);
	vector<int> getKeypieceLoc(string);

	// Computer AI Functions
	// First Pass
	bool keyPieceAttack(string);
	// Second Pass
	bool protectKeyPiece();
	bool executeBlock(int, int);
	// Thrid Pass Move piece that can get closest
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

