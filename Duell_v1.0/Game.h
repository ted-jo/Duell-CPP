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
private:
	Human * humanObj;
	Computer * computerObj;
	bool endGame = false;

};

