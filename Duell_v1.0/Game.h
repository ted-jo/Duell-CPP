#include "stdafx.h"
#include "Human.h"
#include "Computer.h"
#pragma once

class Game
{
public:
	Game();
	~Game();
	void round(string);
	void startGame();
	void setEndGame();
	bool getEndGame() { return endGame; }
	Board getBoard() { return * boardObj; }
	void setBoard(Board *);
	void saveGame(string);
	bool savePrompt(string);
	//void loadGame();
	string firstPlayer();
	void setWinLoad(int, int);
	bool setWin(string player);
	int getHumanWins() { return humanWin; }
	int getComputerWins() { return computerWin; }
	void askHelp();
private:
	Human * humanObj;
	Computer * computerObj;
	Board * boardObj;
	boardView * boardViewObj;
	bool endGame = false;
	int humanWin;
	int computerWin;
};

