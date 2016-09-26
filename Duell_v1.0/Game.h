#include "stdafx.h"
#include "Board.h"
#include "boardView.h"
#include "Die.h"
#include "Human.h"
#include "Computer.h"
#pragma once

class Game
{
public:
	Game();
	~Game();
	void round();
	void startGame();
	void setEndGame();
private:
	Board * boardObj;
	boardView * boardViewObj;
	Human * humanObj;
	Computer * computerObj;
	bool endGame = false;

};

