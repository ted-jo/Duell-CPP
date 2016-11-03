//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "stdafx.h"
#include "Game.h"



#pragma once
class Tournament
{
public:
	Tournament();
	~Tournament();
	// Mutator
	void setBoard();

	void displayWinner();
	void startTournament();
	bool playAgain();
	void loadGame();
	void startFromLoad(string);
	
private:
	Board * boardObj;
	Game * gameObj;
};

