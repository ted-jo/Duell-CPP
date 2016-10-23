//************************************************************
//* Name:  Ted Johansmeyer                                   *
//* Project : C++ Duell                                      *
//* Class : CMPS 366 Organization of Programming Languages   *
//* Date : October 21st 2016                                 *
//************************************************************

#include "stdafx.h"
#include "Human.h"
#include "Computer.h"
#pragma once

class Game
{
public:
	Game();
	~Game();
	string firstPlayer();
	void round(string);
	void saveGame(string);
	bool savePrompt(string);
	void askHelp();
	
	// Set Functions
	void setEndGame();
	void setBoard(Board *);
	void setWinLoad(int, int);
	bool setWin(string player);

	// Get Functions
	Board getBoard() const { return *boardObj; }
	bool getEndGame() const { return endGame; }
	int getHumanWins() const { return humanWin; }
	int getComputerWins() const { return computerWin; }
	
private:
	Human * humanObj;
	Computer * computerObj;
	Board * boardObj;
	boardView * boardViewObj;
	bool endGame;
	int humanWin;
	int computerWin;
};

