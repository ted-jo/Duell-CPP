#include "stdafx.h"
#include "Game.h"



#pragma once
class Tournament
{
public:
	Tournament();
	~Tournament();
	void displayWinner();
	void startTournament();
	bool playAgain();
	void loadGame();
	void startFromLoad(string);
	void setBoard();
private:
	Board * boardObj;
	Game * gameObj;
};

