#include "Game.h"



Game::Game()
{
	boardObj = new Board();
	boardViewObj = new boardView();
}


Game::~Game()
{
}

void Game::round()
{
	//*****Test Code
	int x, y;
	//****************
	
	cout << "Choose X Coordinate of Die to move: ";
	cin >> x;
	cout << "Choose Y Coordinate of Die to move: ";
	cin >> y;
	boardObj->setBoard(boardObj->movePiece(x, y, boardObj->GetBoard()));
	boardViewObj->ViewBoard(boardObj->GetBoard());


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
