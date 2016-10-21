#include "stdafx.h"
#include "Game.h"


#pragma once
class Tournament
{
public:
	Tournament();
	~Tournament() { delete gameObj; }
	//void setComputerWins(int);
	//void setHumanWins(int);
	//int getHumanWins() { return humanWins; }
	//int getComputerWins() { return computerWins; }
	void displayWinner();
	void startTournament();
	bool playAgain();
private:
	int computerWins;
	int humanWins;
	Game * gameObj;
};

