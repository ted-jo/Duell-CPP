#include "stdafx.h"
#include "Board.h"
#include "boardView.h"

#pragma once
class Player
{
public:
	Player();
	~Player();
	bool checkOOB(int, int);
	bool validateMove(int, int, int, int, int, string);
	// Play is virtual so its overwritten in Human and Player. It will control a single turn of play
	virtual void play() = 0;
protected:
	Board * boardObj;
	boardView * boardViewObj;
};

