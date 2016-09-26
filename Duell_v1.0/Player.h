#include "stdafx.h"
#include "Board.h"

#pragma once
class Player
{
public:
	Player() { cout << "\nCreating Players" << endl; }
	~Player();
	bool checkOOB(int, int);

	// Play is virtual so its overwritten in Human and Player. It will control a single turn of play
	virtual void play();
private:
	Board * boardobj;
};

