#include "Game.h"



Game::Game()
{
	boardObj = new Board();
	boardViewObj = new boardView();
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
		humanObj->getCoordinates();

	}
	////*****Test Code
	//int x, y;
	////****************
	//do
	//{
	//	cout << "Choose X Coordinate of Die to move: ";
	//	cin >> x;
	//	cout << "Choose Y Coordinate of Die to move: ";
	//	cin >> y;
	//} while (!boardObj->checkOOB(x, y));

	//boardObj->movePieceUp(x, y);
	//boardViewObj->ViewBoard(boardObj->GetBoard());

	//do
	//{
	//	cout << "Choose X Coordinate of Die to move: ";
	//	cin >> x;
	//	cout << "Choose Y Coordinate of Die to move: ";
	//	cin >> y;
	//} while (!boardObj->checkOOB(x, y));

	//boardObj->movePieceDown(x, y);
	//boardViewObj->ViewBoard(boardObj->GetBoard());


}

void Game::startGame()
{
	// TODO: Add coin flip to see which player goes first

	// Display Starting Board
	boardViewObj->ViewBoard(boardObj->GetBoard());

	while (!endGame)
	{
		round();
	}
}

void Game::setEndGame()
{
	endGame = true;
}
