#include "stdafx.h"
#include "Game.h"



#pragma once
class Tournament
{
public:
	Tournament();
	~Tournament();
	//void setComputerWins(int);
	//void setHumanWins(int);
	//int getHumanWins() { return humanWins; }
	//int getComputerWins() { return computerWins; }
	void displayWinner();
	void startTournament();
	bool playAgain();
	void loadGame();
	void startFromLoad(string);
	void setBoard();
private:
	int computerWins;
	int humanWins;
	Board * boardObj;
	Game * gameObj;
};

