#include "Board.h"
#include "stdafx.h"





Board::~Board()
{
}

void Board::MovePiece()
{
	
}

void Board::ResetBoard(vector<vector<string>> &gameboard)
{
	// Computer Starting Postions
	gameboard[0][0] = "C56";
	gameboard[0][1] = "C15";
	gameboard[0][2] = "C21";
	gameboard[0][3] = "C62";
	gameboard[0][4] = "C11";
	gameboard[0][5] = "C62";
	gameboard[0][6] = "C21";
	gameboard[0][7] = "C15";
	gameboard[0][8] = "C56";
	
	// Human Starting Postions
	gameboard[7][0] = "H56";
	gameboard[7][1] = "H15";
	gameboard[7][2] = "H21";
	gameboard[7][3] = "H62";
	gameboard[7][4] = "H11";
	gameboard[7][5] = "H62";
	gameboard[7][6] = "H21";
	gameboard[7][7] = "H15";
	gameboard[7][8] = "H56";

}



