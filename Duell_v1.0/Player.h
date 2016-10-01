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
	virtual void play() = 0;
	bool checkOOB(int, int);
	bool validateMove(int, int, int, int, int, string);
	void executeMove(int, int, int, int, int, string);
	vector<int> getHumanKeypieceLoc();
	// Computer AI Functions
	// First Pass
	bool keyPieceAttack();

protected:
	Board * boardObj;
	boardView * boardViewObj;
private:
	int humanWin;
	int computerWin;
};

