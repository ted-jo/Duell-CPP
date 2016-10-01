#include "stdafx.h"
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
	Board getBoard() { return * boardObj; }
private:
	Human * humanObj;
	Computer * computerObj;
	Board * boardObj;
	boardView * boardViewObj;
	bool endGame = false;

};

