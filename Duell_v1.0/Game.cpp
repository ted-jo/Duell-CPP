#include "Game.h"



Game::Game()
{
	humanObj = new Human();
	computerObj = new Computer();
}


Game::~Game()
{
}

void Game::round()
{
	while (endGame == false)
	{
		humanObj->play();

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
