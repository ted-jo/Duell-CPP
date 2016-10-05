#include "Game.h"



Game::Game()
{
	humanObj = new Human();
	computerObj = new Computer();
	boardObj = new Board();
	boardViewObj = new boardView();
}


Game::~Game()
{
}

void Game::setBoard(Board * board)
{
	boardObj = board;
}

void Game::round()
{
	while (endGame == false)
	{
		boardViewObj->ViewBoard(boardObj->GetBoard());
		humanObj->setBoard(boardObj);
		setBoard(humanObj->play());
		boardViewObj->ViewBoard(boardObj->GetBoard());
		//computerObj->setBoard(boardObj);
		//setBoard(computerObj->play());
	}
}

void Game::startGame()
{
	// TODO: Add coin flip to see which player goes first

	while (!endGame)
	{
		round();
		setEndGame();
	}
}

void Game::setEndGame()
{
	endGame = true;
}


