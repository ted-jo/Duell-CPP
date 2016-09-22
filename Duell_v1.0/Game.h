#include "stdafx.h"
#include "Board.h"
#include "boardView.h"
#include "Die.h"
#pragma once

class Game
{
public:
	Game();
	~Game();
	void round();
	void startGame();
private:
	Board * boardObj;
	boardView * boardViewObj;
	bool endGame = false;

};

