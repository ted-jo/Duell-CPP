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
	Board getBoard() { return * boardObj; }
	void setBoard(Board *);
	void saveGame(string);
	bool savePrompt(string);
	void loadGame();
	string firstPlayer();
private:
	Human * humanObj;
	Computer * computerObj;
	Board * boardObj;
	boardView * boardViewObj;
	bool endGame = false;

};

