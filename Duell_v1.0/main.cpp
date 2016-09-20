/*
* Driver for the game
*/
#include "stdafx.h"     // Contains the pre-compiled headers.
#include "Board.h"
#include "boardView.h"
#include <stdio.h>


int main(int argc, char *argv[])
{
	// *** Temp
	int x, y;
	// *** Temp
	Board b;
	boardView v;
	vector<vector<Die>> gameboard = b.GetBoard();
	cout << "Start Game" << endl << endl;
	v.ViewBoard(gameboard);
	cout << "Choose X Coordinate of Die to move: ";
	cin >> x;
	cout << "Choose Y Coordinate of Die to move: ";
	cin >> y;
	gameboard = b.movePiece(x, y, gameboard);
	v.ViewBoard(gameboard);


	



	cout << endl;
	system("PAUSE");
	return 0;
}